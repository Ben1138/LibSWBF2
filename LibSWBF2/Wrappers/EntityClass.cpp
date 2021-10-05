#include "pch.h"
#include "EntityClass.h"
#include "InternalHelpers.h"
#include "Hashing.h"
#include "Container.h"

#include "Chunks/LVL/common/GenericClass.h"

#include <string>
#include <map>


typedef LibSWBF2::Chunks::LVL::common::PROP PROP;

namespace LibSWBF2::Wrappers
{
	using LibSWBF2::Chunks::LVL::common::entc;
	using LibSWBF2::Chunks::LVL::common::ordc;
	using LibSWBF2::Chunks::LVL::common::wpnc;
	using LibSWBF2::Chunks::LVL::common::expc;


	class PropertyMap
	{
	public:
		std::unordered_map<FNVHash, std::vector<uint32_t>> m_HashToIndices;
	};


	EntityClass::EntityClass()
	{
		m_PropertyMapping = new PropertyMap();
		p_MainContainer = nullptr;
	}

	EntityClass::~EntityClass()
	{
		delete m_PropertyMapping;
		m_PropertyMapping = nullptr;
	}

	EntityClass& EntityClass::operator=(const EntityClass& other)
	{
		p_MainContainer = other.p_MainContainer;
		p_classChunk = other.p_classChunk;
		m_EntityClassType = other.m_EntityClassType;
		m_PropertyMapping->m_HashToIndices = other.m_PropertyMapping->m_HashToIndices;
		return *this;
	}

	EntityClass& EntityClass::operator=(EntityClass&& other)
	{
		p_MainContainer = other.p_MainContainer;
		p_classChunk = other.p_classChunk;
		m_EntityClassType = other.m_EntityClassType;
		m_PropertyMapping->m_HashToIndices = std::move(other.m_PropertyMapping->m_HashToIndices);
		other.p_MainContainer = nullptr;
		other.p_classChunk = nullptr;
		other.m_EntityClassType = EEntityClassType::GameObjectClass;
		other.m_PropertyMapping = nullptr;
		return *this;
	}

	template<class ChunkType>
	bool EntityClass::FromChunk(Container* mainContainer, ChunkType* classChunk, EntityClass& out)
	{
		if (classChunk == nullptr)
		{
			LOG_ERROR("Given classChunk was NULL!");
			return false;
		}

		out.p_classChunk = (GenericClassNC*)classChunk;
		out.p_MainContainer = mainContainer;

		if (typeid(ChunkType*) == typeid(entc*))
		{
			out.m_EntityClassType = EEntityClassType::GameObjectClass;
		}
		else if (typeid(ChunkType*) == typeid(ordc*))
		{
			out.m_EntityClassType = EEntityClassType::OrdnanceClass;
		}
		else if (typeid(ChunkType*) == typeid(wpnc*))
		{
			out.m_EntityClassType = EEntityClassType::WeaponClass;
		}
		else if (typeid(ChunkType*) == typeid(expc*))
		{
			out.m_EntityClassType = EEntityClassType::ExplosionClass;
		}
		else
		{
			LOG_ERROR("Invalid EntityClass Type: {}", typeid(classChunk).name());
			return false;
		}

		out.m_PropertyMapping->m_HashToIndices.clear();
		for (size_t i = 0; i < classChunk->m_Properties.Size(); ++i)
		{
			FNVHash hashedName = classChunk->m_Properties[i]->m_PropertyName;

			auto it = out.m_PropertyMapping->m_HashToIndices.find(hashedName);
			if (it != out.m_PropertyMapping->m_HashToIndices.end())
			{
				out.m_PropertyMapping->m_HashToIndices[hashedName].push_back((uint32_t)i);
			}
			else
			{
				out.m_PropertyMapping->m_HashToIndices.insert(std::make_pair(hashedName, std::vector<uint32_t>{ (uint32_t)i }));
			}
		}

		return true;
	}

	EEntityClassType EntityClass::GetClassType() const
	{
		return m_EntityClassType;
	}

	const String& EntityClass::GetTypeName() const
	{
		return p_classChunk->p_Type->m_Text;
	}

	const String& EntityClass::GetBaseName() const
	{
		return p_classChunk->p_Base->m_Text;
	}

	const EntityClass* EntityClass::GetBase() const
	{
		if (p_MainContainer == nullptr)
		{
			return nullptr;
		}
		return p_MainContainer->FindEntityClass(GetBaseName());
	}

	bool EntityClass::GetProperty(FNVHash hashedPropertyName, String& outValue) const
	{
		auto it = m_PropertyMapping->m_HashToIndices.find(hashedPropertyName);
		if (it != m_PropertyMapping->m_HashToIndices.end() && it->second.size() > 0)
		{
			outValue = p_classChunk->m_Properties[it->second[0]]->m_Value;
			return true;
		}
		const EntityClass* base = GetBase();
		if (base != nullptr)
		{
			return base->GetProperty(hashedPropertyName, outValue);
		}
		return false;
	}

	bool EntityClass::GetProperty(const String& propertyName, String& outValue) const
	{
		if (propertyName.IsEmpty())
		{
			return false;
		}
		return GetProperty(FNV::Hash(propertyName), outValue);
	}

	bool EntityClass::GetProperty(const String& propertyName, List<String>& outValues) const
	{
		if (propertyName.IsEmpty())
		{
			return false;
		}
		return GetProperty(FNV::Hash(propertyName), outValues);
	}

	bool EntityClass::GetProperty(FNVHash hashedPropertyName, List<String>& outValues) const
	{
		auto it = m_PropertyMapping->m_HashToIndices.find(hashedPropertyName);
		if (it != m_PropertyMapping->m_HashToIndices.end() && it->second.size() > 0)
		{
			for (size_t i = 0; i < it->second.size(); ++i)
			{
				outValues.Add(p_classChunk->m_Properties[it->second[i]]->m_Value);
			}

			// For multi properties (e.g. ControlSpeed) also crawl down
			// all the base classes for that same property name.
			// So we actually do NOT return here.
		}

		const EntityClass* base = GetBase();
		if (base != nullptr)
		{
			base->GetProperty(hashedPropertyName, outValues);
		}
		return outValues.Size() > 0;
	}

	void EntityClass::GetOverriddenProperties(List<FNVHash>& outHashes, List<String>& outValues) const
	{
		outHashes.Clear();
		outValues.Clear();

		List<PROP*>& properties = p_classChunk -> m_Properties;
		for (int i = 0; i < properties.Size(); i++)
		{
			outHashes.Add(properties[i] -> m_PropertyName);
			outValues.Add(properties[i] -> m_Value);
		}
	}

	void EntityClass::GetAllProperties(List<FNVHash>& outHashes, List<String>& outValues) const
	{
		outHashes.Clear();
		outValues.Clear();

		const EntityClass* base = GetBase();
		if (base != nullptr)
		{
			base->GetAllProperties(outHashes, outValues);
		}

		List<PROP*>& properties = p_classChunk->m_Properties;
		for (int i = 0; i < properties.Size(); i++)
		{
			outHashes.Add(properties[i]->m_PropertyName);
			outValues.Add(properties[i]->m_Value);
		}
	}
	

	template LIBSWBF2_API bool EntityClass::FromChunk(Container* mainContainer, entc* classChunk, EntityClass& out);
	template LIBSWBF2_API bool EntityClass::FromChunk(Container* mainContainer, ordc* classChunk, EntityClass& out);
	template LIBSWBF2_API bool EntityClass::FromChunk(Container* mainContainer, wpnc* classChunk, EntityClass& out);
	template LIBSWBF2_API bool EntityClass::FromChunk(Container* mainContainer, expc* classChunk, EntityClass& out);
}