#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
#include "Chunks/STRMULT.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
	struct LIBSWBF2_API anmg : public GenericChunk<"anmg"_m>
	{
	public:

		STR<"INFO"_m> *p_Info;

		List<STRMULT<"ANIM"_m> *> m_AnimObjectPairs;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}