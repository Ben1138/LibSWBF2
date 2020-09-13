#include "stdafx.h"
#include "Instance.h"
#include "Types/LibString.h"
#include "InternalHelpers.h"
#include "Hashing.h"
#include "Level.h"

namespace LibSWBF2::Wrappers
{
	class PropertyMap
	{
	public:
		std::unordered_map<FNVHash, uint32_t> m_HashToIndex;
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
		p_Parent = other.p_Parent;
		p_Instance = other.p_Instance;
		m_PropertyMapping->m_HashToIndex = other.m_PropertyMapping->m_HashToIndex;
		return *this;
	}

	Instance& Instance::operator=(Instance&& other)
	{
		p_Parent = other.p_Parent;
		p_Instance = other.p_Instance;
		other.m_PropertyMapping = new PropertyMap();
		return *this;
	}

	bool Instance::FromChunk(Level* mainContainer, inst* instanceChunk, Instance& out)
	{
		if (mainContainer == nullptr)
		{
			LOG_ERROR("Given mainContainer was NULL!");
			return false;
		}
		if (instanceChunk == nullptr)
		{
			LOG_ERROR("Given instanceChunk was NULL!");
			return false;
		}

		out.p_Parent = mainContainer;
		out.p_Instance = instanceChunk;

		instanceChunk->m_OverrideProperties.Clear();
		for (size_t i = 0; i < instanceChunk->m_OverrideProperties.Size(); ++i)
		{
			FNVHash hashedName = instanceChunk->m_OverrideProperties[i]->m_PropertyName;
			out.m_PropertyMapping->m_HashToIndex.emplace(hashedName, (uint32_t)i);
		}

		return true;
	}

	String Instance::GetType() const
	{
		return p_Instance->p_Info->p_Type->m_Text;
	}

	String Instance::GetName() const
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
		return p_Parent->GetEntityClass(GetType());
	}

	bool Instance::GetProperty(FNVHash hashedPropertyName, String& outValue) const
	{
		auto it = m_PropertyMapping->m_HashToIndex.find(hashedPropertyName);
		if (it != m_PropertyMapping->m_HashToIndex.end())
		{
			outValue = p_Instance->m_OverrideProperties[it->second]->m_Value;
			return true;
		}
		
		const EntityClass* entityClass = GetEntityClass();
		if (entityClass == nullptr)
		{
			LOG_WARN("Could not resolve Entity Class '{}' from instance '{}'", GetType(), GetName());
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

	const Model* Instance::GetGeometry() const
	{
		String outGeometryName;
		if (GetProperty("GeometryName", outGeometryName))
		{
			return p_Parent->GetModel(outGeometryName);
		}
		return nullptr;
	}
}