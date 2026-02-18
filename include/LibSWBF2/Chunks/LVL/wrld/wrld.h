#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Chunks/STR.h>
#include <LibSWBF2/Chunks/STRMULT.h>
#include <LibSWBF2/Chunks/LVL/wrld/inst.h>
#include <LibSWBF2/Chunks/LVL/wrld/regn.h>
#include <LibSWBF2/Chunks/LVL/wrld/anmg.h>
#include <LibSWBF2/Chunks/LVL/wrld/anim.h>
#include <LibSWBF2/Chunks/LVL/wrld/anmh.h>
#include <LibSWBF2/Chunks/LVL/wrld/BARR.h>
#include <LibSWBF2/Chunks/LVL/wrld/Hint.h>


namespace LibSWBF2::Chunks::LVL::wrld
{
	struct LIBSWBF2_API wrld : public GenericChunk<"wrld"_m>
	{
	public:
		STR<"NAME"_m>* p_Name;
		STR<"TNAM"_m>* p_TerrainName;	// optional chunk, can be nullptr
		STR<"SNAM"_m>* p_SkyName;		// optional chunk, can be nullptr

		// a.k.a. objects placed into the world
		List<inst*> m_Instances;

		List<regn*> m_Regions;

		List<anim*> m_Animations;
		List<anmg*> m_AnimationGroups;
		List<anmh*> m_AnimationHierarchies;

		List<BARR*> m_Barriers;
		List<Hint*> m_HintNodes;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}