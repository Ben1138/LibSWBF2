#pragma once
#include "SoundBaseChunk.h"

namespace LibSWBF2::Chunks::LVL::sound
{
	struct StreamInfo;
	struct SoundData;

	struct LIBSWBF2_API Stream : public SoundBaseChunk<"Stream"_fnv>
	{
		StreamInfo *p_Info;
		List<SoundData *> m_DataChunks;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}