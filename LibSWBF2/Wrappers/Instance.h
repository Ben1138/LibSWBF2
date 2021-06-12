#pragma once
#include "req.h"
#include "EntityClass.h"
#include "Types/Vector4.h"
#include "Types/List.h"
#include "Chunks/LVL/wrld/inst.h"

namespace LibSWBF2
{
	class Container;
}

namespace LibSWBF2::Wrappers
{
	using namespace LibSWBF2::Chunks::LVL::wrld;
	using Types::Vector3;
	using Types::Vector4;
	using Types::List;
	using Types::String;

	class Level;
	class Model;
	class World;

	class LIBSWBF2_API Instance
	{
	private:
		friend World;
		friend List<Instance>;

		Instance();
		~Instance();

		Instance& operator=(const Instance& other);
		Instance& operator=(Instance&& other);

	private:
		Container* p_MainContainer;
		inst* p_Instance;
		class PropertyMap* m_PropertyMapping;

	public:
		static bool FromChunk(Container* mainContainer, inst* instanceChunk, Instance& out);

		const String& GetEntityClassName() const;
		const String& GetName() const;
		Vector3 GetPosition() const;
		Vector4 GetRotation() const;

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

		void GetOverriddenProperties(List<FNVHash>& hashesOut, List<String>& valuesOut) const;
		const EntityClass* GetEntityClass() const;
	};
}