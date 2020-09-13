#pragma once
#include "req.h"
#include "EntityClass.h"
#include "Types/Vector4.h"
#include "Types/List.h"
#include "Chunks/LVL/wrld/inst.h"

namespace LibSWBF2::Wrappers
{
	using LibSWBF2::Chunks::LVL::wrld::inst;
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

	private:
		Level* p_Parent;
		inst* p_Instance;
		class PropertyMap* m_PropertyMapping;

	public:
		static bool FromChunk(Level* mainContainer, inst* instanceChunk, Instance& out);

		String GetType() const;
		String GetName() const;
		Vector3 GetPosition() const;
		Vector4 GetRotation() const;
		const EntityClass* GetEntityClass() const;

		// will fallback to entity class property, if existent
		bool GetProperty(FNVHash hashedPropertyName, String& outValue) const;

		// will fallback to entity class property, if existent
		bool GetProperty(const String& propertyName, String& outValue) const;

		// will return 'nullptr' if no geometry has been specified
		const Model* GetGeometry() const;
	};
}