#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STRMULT.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
	struct anmg_INFO;

	struct LIBSWBF2_API anmg : public GenericChunk<"anmg"_m>
	{
	public:

		anmg_INFO *p_Info;

		List<STRMULT<"ANIM"_m> *> m_AnimObjectPairs;

		GenericChunk<"NOHI"_m> * p_NoHierarchy; 

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}