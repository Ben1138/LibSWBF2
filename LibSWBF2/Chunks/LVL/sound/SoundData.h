#pragma once
#include "Chunks/GenericChunk.h"

namespace LibSWBF2::Chunks::LVL::sound
{
	struct LIBSWBF2_API SoundData : public GenericChunk<"Data"_fnv>
	{
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}