#pragma once
#include "req.h"
#include "Instance.h"
#include "Terrain.h"
#include "Light.h"
#include "Chunks/LVL/wrld/wrld.h"

namespace LibSWBF2
{
	class Container;
}

namespace LibSWBF2::Wrappers
{
	using Types::List;
	using Chunks::LVL::wrld::wrld;

	class Level;

	class LIBSWBF2_API World
	{
	private:
		friend Level;
		friend List<World>;

		World() = default;
		~World() = default;

		Container* m_MainContainer = nullptr;

	private:
		wrld* p_World;
		List<Instance> m_Instances;	// a.k.a. world objects
		List<Light> m_Lights;

	public:
		static bool FromChunk(Container* mainContainer, wrld* worldChunk, World& out);

		const String& GetName() const;
		const List<Instance>& GetInstances() const;
		Types::String GetTerrainName() const;
		const Terrain* GetTerrain() const;
		Types::String GetSkyName() const;

		const List<Light>& GetLights() const;
	};
}