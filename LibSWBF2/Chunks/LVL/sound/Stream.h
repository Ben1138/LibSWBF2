#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/RawData.h"

namespace LibSWBF2::Chunks::LVL::sound
{
	struct StreamInfo;
	struct StreamData;

	struct LIBSWBF2_API Stream : public GenericChunk<"Stream"_fnv>
	{
		StreamInfo *p_Info;
		StreamData *p_Data;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}