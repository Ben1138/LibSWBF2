#include "stdafx.h"
#include "Instance.h"
#include "Types/LibString.h"
#include "InternalHelpers.h"
#include "Hashing.h"
#include "Level.h"
#include "Container.h"

namespace LibSWBF2::Wrappers
{
	class PropertyMap
	{
	public:
		std::unordered_map<FNVHash, std::vector<uint32_t>> m_HashToIndices;
	};


	Instance::Instance()
	{
		m_PropertyMapping = new PropertyMap();
	}

	Instance::~Instance()
	{
		delete m_PropertyMapping;
	}

	Instance& Instance::operator=(const Instance& other)
	{
		p_MainContainer = other.p_MainContainer;
		p_Instance = other.p_Instance;
		m_PropertyMapping->m_HashToIndices = other.m_PropertyMapping->m_HashToIndices;
		return *this;
	}
	
	Instance& Instance::operator=(Instance&& other)
	{
		p_MainContainer = other.p_MainContainer;
		p_Instance = other.p_Instance;
		other.m_PropertyMapping = new PropertyMap();
		return *this;
	}

	bool Instance::FromChunk(Container* mainContainer, inst* instanceChunk, Instance& out)
	{
		if (instanceChunk == nullptr)
		{
			LOG_ERROR("Given instanceChunk was NULL!");
			return false;
		}

		out.p_MainContainer = mainContainer;
		out.p_Instance = instanceChunk;

		out.m_PropertyMapping->m_HashToIndices.clear();
		for (size_t i = 0; i < instanceChunk->m_OverrideProperties.Size(); ++i)
		{
			FNVHash hashedName = instanceChunk->m_OverrideProperties[i]->m_PropertyName;

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

	const String& Instance::GetType() const
	{
		return p_Instance->p_Info->p_Type->m_Text;
	}

	const String& Instance::GetName() const
	{
		return p_Instance->p_Info->p_Name->m_Text;
	}

	Vector3 Instance::GetPosition() const
	{
		return p_Instance->p_Info->p_XFRM->m_Position;
	}

	Vector4 Instance::GetRotation() const
	{
		return MatrixToQuaternion(p_Instance->p_Info->p_XFRM->m_RotationMatrix);
	}

	const EntityClass* Instance::GetEntityClass() const
	{
		if (p_MainContainer == nullptr)
		{
			return nullptr;
		}
		return p_MainContainer->FindEntityClass(GetType());
	}

	bool Instance::GetProperty(FNVHash hashedPropertyName, String& outValue) const
	{
		auto it = m_PropertyMapping->m_HashToIndices.find(hashedPropertyName);
		if (it != m_PropertyMapping->m_HashToIndices.end() && it->second.size() > 0)
		{
			outValue = p_Instance->m_OverrideProperties[it->second[0]]->m_Value;
			return true;
		}
		
		const EntityClass* entityClass = GetEntityClass();
		if (entityClass == nullptr)
		{
			// This can happen if the Entity Class is in another LVL (e.g. com_bldg_controlzone)
			// and there's no Container above the currently owning Level instance
			return false;
		}

		return entityClass->GetProperty(hashedPropertyName, outValue);
	}

	bool Instance::GetProperty(const String& propertyName, String& outValue) const
	{
		if (propertyName.IsEmpty())
		{
			return false;
		}
		return GetProperty(FNV::Hash(propertyName), outValue);
	}

	bool Instance::GetProperty(const String& propertyName, List<String>& outValues) const
	{
		if (propertyName.IsEmpty())
		{
			return false;
		}
		return GetProperty(FNV::Hash(propertyName), outValues);
	}

	bool Instance::GetProperty(FNVHash hashedPropertyName, List<String>& outValues) const
	{
		outValues.Clear();
		auto it = m_PropertyMapping->m_HashToIndices.find(hashedPropertyName);
		if (it != m_PropertyMapping->m_HashToIndices.end() && it->second.size() > 0)
		{
			for (size_t i = 0; i < it->second.size(); ++i)
			{
				outValues.Add(p_Instance->m_OverrideProperties[it->second[i]]->m_Value);
			}
			return true;
		}
		const EntityClass* instanceClass = GetEntityClass();
		if (instanceClass != nullptr)
		{
			return instanceClass->GetProperty(hashedPropertyName, outValues);
		}
		return false;
	}

	bool Instance::GetOverriddenProperties(List<FNVHash>& hashesOut, List<String>& valuesOut) const
	{
		List<FNVHash> hashes;
		List<String> values;

		List<PROP*>& properties = p_Instance -> m_OverrideProperties;

		for (int i = 0; i < properties.Size(); i++)
		{
			hashes.Add(properties[i] -> m_PropertyName);
			values.Add(properties[i] -> m_Value);
		}

		hashesOut = std::move(hashes);
		valuesOut = std::move(values);

		return true;
	}
}