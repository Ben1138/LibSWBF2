#include "stdafx.h"
#include "EntityClass.h"
#include "InternalHelpers.h"
#include "Hashing.h"
#include "Chunks/LVL/tex_/tex_.LVL_.h"
#include <string>
#include <map>

namespace LibSWBF2::Wrappers
{
	using LibSWBF2::Chunks::LVL::common::entc;
	using LibSWBF2::Chunks::LVL::common::ordc;
	using LibSWBF2::Chunks::LVL::common::wpnc;
	using LibSWBF2::Chunks::LVL::common::expc;


	class PropertyMap
	{
	public:
		std::unordered_map<FNVHash, uint32_t> m_HashToIndex;
	};


	EntityClass::EntityClass()
	{
		m_PropertyMapping = new PropertyMap();
	}

	EntityClass::~EntityClass()
	{
		delete m_PropertyMapping;
		m_PropertyMapping = nullptr;
	}

	EntityClass& EntityClass::operator=(const EntityClass& other)
	{
		p_classChunk = other.p_classChunk;
		m_EntityClassType = other.m_EntityClassType;
		m_PropertyMapping->m_HashToIndex = other.m_PropertyMapping->m_HashToIndex;
		return *this;
	}

	EntityClass& EntityClass::operator=(EntityClass&& other)
	{
		p_classChunk = other.p_classChunk;
		m_PropertyMapping = other.m_PropertyMapping;
		other.m_PropertyMapping = new PropertyMap();
		return *this;
	}

	template<class EntityClassType>
	bool EntityClass::FromChunk(EntityClassType* classChunk, EntityClass& out)
	{
		if (classChunk == nullptr)
		{
			LOG_ERROR("Given classChunk was NULL!");
			return false;
		}

		out.p_classChunk = (GenericClassNC*)classChunk;

		if (typeid(EntityClassType*) == typeid(entc*))
		{
			out.m_EntityClassType = EEntityClassType::GameObjectClass;
		}
		else if (typeid(EntityClassType*) == typeid(ordc*))
		{
			out.m_EntityClassType = EEntityClassType::OrdnanceClass;
		}
		else if (typeid(EntityClassType*) == typeid(wpnc*))
		{
			out.m_EntityClassType = EEntityClassType::WeaponClass;
		}
		else if (typeid(EntityClassType*) == typeid(expc*))
		{
			out.m_EntityClassType = EEntityClassType::ExplosionClass;
		}
		else
		{
			LOG_ERROR("Invalid EntityClass Type: {}", typeid(classChunk).name());
			return false;
		}

		out.m_PropertyMapping->m_HashToIndex.clear();
		for (size_t i = 0; i < classChunk->m_Properties.Size(); ++i)
		{
			FNVHash hashedName = classChunk->m_Properties[i]->m_PropertyName;
			out.m_PropertyMapping->m_HashToIndex.emplace(hashedName, (uint32_t)i);
		}

		return true;
	}

	String EntityClass::GetClassType() const
	{
		return p_classChunk->p_Type->m_Text;
	}

	String EntityClass::GetClassBase() const
	{
		return p_classChunk->p_Base->m_Text;
	}

	bool EntityClass::GetProperty(FNVHash hashedPropertyName, String& outValue) const
	{
		auto it = m_PropertyMapping->m_HashToIndex.find(hashedPropertyName);
		if (it != m_PropertyMapping->m_HashToIndex.end())
		{
			outValue = p_classChunk->m_Properties[it->second]->m_Value;
			return true;
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
	

	template LIBSWBF2_API bool EntityClass::FromChunk(entc* classChunk, EntityClass& out);
	template LIBSWBF2_API bool EntityClass::FromChunk(ordc* classChunk, EntityClass& out);
	template LIBSWBF2_API bool EntityClass::FromChunk(wpnc* classChunk, EntityClass& out);
	template LIBSWBF2_API bool EntityClass::FromChunk(expc* classChunk, EntityClass& out);
}