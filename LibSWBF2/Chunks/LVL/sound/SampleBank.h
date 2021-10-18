#pragma once
#include "SoundBaseChunk.h"

namespace LibSWBF2::Chunks::LVL::sound
{
	struct SampleBankInfo;
	struct StreamData;

	struct LIBSWBF2_API SampleBank : public SoundBaseChunk<"SampleBank"_fnv>
	{
		SampleBankInfo *p_Info;
		List<StreamData *> m_DataChunks;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}