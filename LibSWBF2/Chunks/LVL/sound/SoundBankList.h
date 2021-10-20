#pragma once
#include "Chunks/GenericChunk.h"

namespace LibSWBF2::Chunks::LVL::sound
{
	struct SampleBank;

	struct LIBSWBF2_API SoundBankList : public GenericChunk<"SoundBankList"_fnv>
	{
		List<SampleBank *> m_SampleBanks;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}