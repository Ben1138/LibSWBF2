#pragma once
#include "Types/Enums.h"
#include "Types/List.h"

namespace LibSWBF2
{
	class Container;

	namespace Chunks::LVL::common
	{
		struct GenericClassNC;
	}
}

namespace LibSWBF2::Wrappers
{
	using LibSWBF2::Types::String;
	using LibSWBF2::Types::List;


	class LIBSWBF2_API EntityClass
	{
	typedef LibSWBF2::Chunks::LVL::common::GenericClassNC GenericClassNC;


	private:
		friend class Level;
		friend List<EntityClass>;

		EntityClass();
		~EntityClass();

		EntityClass& operator=(const EntityClass& other);
		EntityClass& operator=(EntityClass&& other);

	private:
		Container* p_MainContainer;
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
		static bool FromChunk(Container* mainContainer, EntityClassType* classChunk, EntityClass& out);

		String GetTypeName() const;
		String GetBaseName() const;
		const EntityClass* GetBase() const;

		// will fall back to base class, if existent
		bool GetProperty(FNVHash hashedPropertyName, String& outValue) const;

		// will fall back to base class, if existent
		bool GetProperty(const String& propertyName, String& outValue) const;



		bool GetOverriddenProperties(List<FNVHash>& hashes, List<String>& values) const;
	};
}