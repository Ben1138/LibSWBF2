#pragma once
#include "req.h"

#include "Types/LibString.h"
#include "Types/List.h"
#include "Types/Vector3.h"
#include "Types/Vector4.h"


namespace LibSWBF2
{
	class Container;

	namespace Chunks::LVL::wrld
	{
		struct wrld;
		struct regn;
	}
}


namespace LibSWBF2::Wrappers
{
	using Types::List;
	using Types::String;
	using Types::Vector3;
	using Types::Vector4;

	class Level;
	class Instance;
	class Terrain;
	class World;


	class LIBSWBF2_API Region
	{
	typedef LibSWBF2::Chunks::LVL::wrld::regn regn;

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
	typedef LibSWBF2::Chunks::LVL::wrld::wrld wrld;

	private:
		friend Level;
		friend List<World>;

		World() = default;
		~World() = default;

		Container* m_MainContainer = nullptr;

		List<Instance> m_Instances;	// a.k.a. world objects
		List<Region> m_Regions;

		wrld* p_World;


	public:
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