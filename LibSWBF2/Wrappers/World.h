#pragma once
#include "req.h"
#include "Instance.h"
#include "Chunks/LVL/wrld/wrld.h"

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

	private:
		wrld* p_World;
		List<Instance> m_Instances;	// a.k.a. world objects

	public:
		static bool FromChunk(Level* mainContainer, wrld* worldChunk, World& out);

		const String& GetName() const;
		const List<Instance>& GetInstances() const;
		Types::String GetTerrainName() const;
		Types::String GetSkyName() const;
	};
}