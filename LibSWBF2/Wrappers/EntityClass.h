#pragma once
#include "Chunks/LVL/common/GenericClass.h"
#include "Types/Enums.h"
#include "Types/List.h"

namespace LibSWBF2::Wrappers
{
	using LibSWBF2::Chunks::LVL::common::GenericClassNC;
	using LibSWBF2::Types::String;
	using LibSWBF2::Types::List;


	class LIBSWBF2_API EntityClass
	{
	private:
		friend class Level;
		friend List<EntityClass>;

		EntityClass();
		~EntityClass();

		EntityClass& operator=(const EntityClass& other);
		EntityClass& operator=(EntityClass&& other);

	private:
		GenericClassNC* p_classChunk;
		EEntityClassType m_EntityClassType;
		class PropertyMap* m_PropertyMapping;

	public:
		// Only available template instances for "FromChunk" are:
		// - entc*
		// - ordc*
		// - wpnc*
		// - expc*
		template<class EntityClassType>
		static bool FromChunk(EntityClassType* classChunk, EntityClass& out);

		String GetClassType() const;
		String GetClassBase() const;
		bool GetProperty(FNVHash hashedPropertyName, String& outValue) const;
		bool GetProperty(const String& propertyName, String& outValue) const;
	};
}