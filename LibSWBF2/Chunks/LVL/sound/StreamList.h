#pragma once
#include "SoundBaseChunk.h"

namespace LibSWBF2::Chunks::LVL::sound
{
	struct Stream;

	struct LIBSWBF2_API StreamList : public SoundBaseChunk<"StreamList"_fnv>
	{
		List<Stream *> m_Streams;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}