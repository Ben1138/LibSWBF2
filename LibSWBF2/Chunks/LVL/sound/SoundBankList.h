#pragma once
#include "Chunks/GenericChunk.h"
#include "SoundBaseChunk.h"
#include "Types/SoundBankHeader.h"

namespace LibSWBF2::Chunks::LVL::sound
{
	using Types::SoundBankHeader;

	struct LIBSWBF2_API SoundBankList : public SoundBaseChunk<"SoundBankList"_fnv>
	{
		SoundBankHeader m_SoundBankHeader;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}