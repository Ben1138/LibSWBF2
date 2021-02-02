#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
#include "inst.h"
#include "regn.h"

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

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}