#pragma once
#include "req.h"
#include "Instance.h"
#include "Terrain.h"
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


	class LIBSWBF2_API Region
	{
		friend World;
		friend List<Region>;

		regn* p_Region;
		Region() = default;
		static bool FromChunk(regn* chunk, Region& regOut);

	public:
		const String& GetName() const;
		const Vector3& GetPosition() const;
		Vector4 GetRotation() const;
		const String& GetType() const;
		const Vector3& GetSize() const;
	};


	class LIBSWBF2_API World
	{
	private:
		friend Level;
		friend List<World>;

		World() = default;
		~World() = default;

		Container* m_MainContainer = nullptr;

		List<Instance> m_Instances;	// a.k.a. world objects
		List<Region> m_Regions;

	public:

		wrld* p_World;

		static bool FromChunk(Container* mainContainer, wrld* worldChunk, World& out);

		const String& GetName() const;
		const List<Instance>& GetInstances() const;
		const List<Region>& GetRegions() const;
		Types::String GetTerrainName() const;
		const Terrain* GetTerrain() const;
		Types::String GetSkyName() const;


		//const List<String>& GetAnimationNames();
		//const List<String>& GetAnimationGroup(const String& animName);
		//const bool GetAnimationCurve(const String& animName, ECurveComponent cc, Curve& curveOut);
	};
}