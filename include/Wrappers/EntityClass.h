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
		template<class ChunkType>
		static bool FromChunk(Container* mainContainer, ChunkType* classChunk, EntityClass& out);

		EEntityClassType GetClassType() const;
		const String& GetTypeName() const;
		const String& GetBaseName() const;
		const EntityClass* GetBase() const;

		// Note about properties:
		// Property names are not unique! There's potentially more than one
		// property under one name. Example from com_bldg_controlzone:
		//   HoloImageGeometry = "com_icon_alliance alliance"
		//   HoloImageGeometry = "com_icon_imperial empire"
		//   HoloImageGeometry = "com_icon_republic republic"
		//   HoloImageGeometry = "com_icon_CIS CIS"

		// these will return the first encounter. will fall back to base class, if existent
		bool GetProperty(FNVHash hashedPropertyName, String& outValue) const;
		bool GetProperty(const String& propertyName, String& outValue) const;

		// these will return all encounters. will also recursively search base classes, if existent
		bool GetProperty(const String& propertyName, List<String>& outValues) const;
		bool GetProperty(FNVHash hashedPropertyName, List<String>& outValues) const;

		void GetOverriddenProperties(List<FNVHash>& outHashes, List<String>& outValues) const;
		void GetAllProperties(List<FNVHash>& outHashes, List<String>& outValues) const;
	};
}