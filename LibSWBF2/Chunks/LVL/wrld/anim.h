#pragma once
#include "Chunks/GenericChunk.h"
#include "INFO_STR.h"
#include "Chunks/RawData.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
	struct LIBSWBF2_API anim : public GenericChunk<"anim"_m>
	{
	public:

		anim_INFO *p_Info;

		List<RawData<"POSK"_m> *> m_PositionKeys;
		List<RawData<"ROTK"_m> *> m_RotationKeys;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}