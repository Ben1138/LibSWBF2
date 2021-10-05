#include "req.h"
#include "pch.h"
#include "Config.h"
#include "Chunks/LVL/config/ConfigChunk.h"
#include "Chunks/LVL/config/SCOP.h"
#include "InternalHelpers.h"


namespace LibSWBF2::Wrappers
{
	using namespace LibSWBF2::Chunks::LVL::config;
	using namespace LibSWBF2::Types;


	/*

	Field

	*/

	List<Field> Field::FieldsFromChunkChildren(GenericBaseChunk *chunk)
	{
		List<Field> fields;
		const List<GenericBaseChunk *>& children = chunk -> GetChildren();
		
		for (uint16_t i = 0; i < children.Size(); i++)
		{
			DATA_CONFIG *child = dynamic_cast<DATA_CONFIG *>(children[i]);
			
			if (child == nullptr) continue;
			
			SCOP *scope;
			if (i == children.Size() - 1)
			{
				scope = nullptr;
			}
			else
			{
				scope = dynamic_cast<SCOP *>(children[i+1]);
			}
				
			fields.Add(Field(child, scope));
		}

		return fields;
	}


	Field::Field(DATA_CONFIG *data, SCOP* scop) : m_Scope(scop)
	{
		p_Data = data;
	}

	FNVHash Field::GetNameHash() const
	{
		return p_Data->m_NameHash;
	}

	uint8_t Field::GetNumValues() const
	{
		return p_Data->m_NumValues;
	}

	EDataValueType Field::GetValueType(uint8_t index) const
	{
		EDataValueType out;
		if (p_Data->GetValueType(out, index))
		{
			return out;
		}

		LOG_WARN("Could not get field value type at index {0} in DATA chunk '{1}'!", index, GetName().Buffer());
		return EDataValueType::Float;
	}

	float_t Field::GetFloat(uint8_t index) const
	{	
		float_t out;
		if (p_Data->GetFloat(out, index))
		{
			return out;
		}
		
		LOG_WARN("Could not get field float value at index {0} in DATA chunk '{1}'!", index, GetName().Buffer());
		return 0.0f;
	}
		

	Vector2 Field::GetVector2() const
	{
		Vector2 out;
		if (p_Data->GetVec2(out))
		{
			return out;
		}

		LOG_WARN("Could not get field Vector2 value in DATA chunk '{0}'!", GetName().Buffer());
		return Vector2();
	}


	Vector3 Field::GetVector3() const
	{
		Vector3 out;
		if (p_Data->GetVec3(out))
		{
			return out;
		}

		LOG_WARN("Could not get field Vector3 value in DATA chunk '{0}'!", GetName().Buffer());
		return Vector3();
	}


	Vector4 Field::GetVector4() const
	{
		Vector4 out;
		if (p_Data->GetVec4(out))
		{
			return out;
		}

		LOG_WARN("Could not get field Vector4 value in DATA chunk '{0}'!", GetName().Buffer());
		return Vector4();
	}


	String Field::GetString(uint8_t index) const
	{
		String strOut;
		if (p_Data->GetString(strOut, index))
		{
			return strOut;
		}
	
		LOG_WARN("Could not get field string value at index {0} in DATA chunk '{1}'!", index, GetName().Buffer());
		return "";
	}

	String Field::GetName() const
	{
		String name;
		if (!FNV::Lookup(p_Data->m_NameHash, name))
		{
			name = fmt::format("0x{0:x}", p_Data->m_NameHash).c_str();
		}
		return name;
	}


	/*

	Scope

	*/

	const void Scope::Cache() const
	{
		m_Fields = std::move(Field::FieldsFromChunkChildren(p_Scope));
		m_IsValid = true;
	}

	bool Scope::IsEmpty() const
	{
		if (!m_IsValid)
		{
			Cache();
		}
		return m_Fields.Size() == 0;
	}


	const Field& Scope::GetField(FNVHash name) const
	{
		if (!m_IsValid)
		{
			Cache();
		}

		for (uint16_t i = 0; i < m_Fields.Size(); i++)
		{
			const Field& cur = m_Fields[i];
			if (name == 0 || cur.p_Data->m_NameHash == name)
			{
				return cur;
			}
		}
		THROW("Field not found!");
	}


	List<const Field *> Scope::GetFields(FNVHash name) const
	{
		if (!m_IsValid)
		{
			Cache();
		}

		List<const Field *> matchedFields;
		for (uint16_t i = 0; i < m_Fields.Size(); i++)
		{
			const Field& cur = m_Fields[i];
			if (name == 0 || cur.p_Data->m_NameHash == name)
			{
				matchedFields.Add(&cur);
			}
		}
		return matchedFields;
	}


	Scope::Scope(SCOP *scopePtr)
	{
		p_Scope = scopePtr;
		m_IsValid = false;
	}




	/*

	Config

	*/

	const Field& Config::GetField(FNVHash name) const
	{
		for (uint16_t i = 0; i < m_Fields.Size(); i++)
		{
			const Field& cur = m_Fields[i];
			if (name == 0 || cur.p_Data->m_NameHash == name)
			{
				return cur;
			}
		}
		THROW("Field not found!");
	}


	List<const Field *> Config::GetFields(FNVHash name) const
	{
		List<const Field *> matchedFields;
		for (uint16_t i = 0; i < m_Fields.Size(); i++)
		{
			const Field& cur = m_Fields[i];
			if (name == 0 || cur.p_Data->m_NameHash == name)
			{
				matchedFields.Add(&cur);
			}
		}
		return matchedFields;
	}


	bool Config::FromChunk(GenericBaseChunk *cfgPtr, Config& wrapperOut)
	{
		const List<GenericBaseChunk *>& children = cfgPtr -> GetChildren();

		if (children.Size() == 0) return false;
		
		config_NAME* nameChunk = dynamic_cast<config_NAME *>(children[0]);
		
		if (nameChunk == nullptr) return false;

		EConfigType type;

		if (dynamic_cast<comb*>(cfgPtr) != nullptr)
		{
			type = EConfigType::Combo;
		}
		else if (dynamic_cast<lght*>(cfgPtr) != nullptr)
		{
			type = EConfigType::Lighting;
		}
		else if (dynamic_cast<path*>(cfgPtr) != nullptr)
		{
			type = EConfigType::Path;
		}
		else if (dynamic_cast<bnd_*>(cfgPtr) != nullptr)
		{
			type = EConfigType::Boundary;
		}
		else if (dynamic_cast<fx__*>(cfgPtr) != nullptr)
		{
			type = EConfigType::Effect;
		}
		else if (dynamic_cast<sky_*>(cfgPtr) != nullptr)
		{
			type = EConfigType::Skydome;
		}
		else 
		{
			LOG_ERROR("Couldn't wrap unhandled config chunk...");
			return false;
		}

		wrapperOut.m_Type = type; 
		wrapperOut.p_Chunk = (ConfigChunkNC *) cfgPtr;
		wrapperOut.m_Fields = Field::FieldsFromChunkChildren(cfgPtr);
		wrapperOut.m_Name = nameChunk -> m_Name;

		return true;
	}
}
