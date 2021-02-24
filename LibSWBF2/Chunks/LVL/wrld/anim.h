#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/RawData.h"
#include "Chunks/STR.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
	struct LIBSWBF2_API anim : public GenericChunk<"anim"_m>
	{
	public:

		STR<"INFO"_m>* p_Info;

		List<RawData<"POSK"_m> *> m_PositionKeys;
		List<RawData<"ROTK"_m> *> m_RotationKeys;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}