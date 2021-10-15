#pragma once
#include "SoundBaseChunk.h"

namespace LibSWBF2::Chunks::LVL::sound
{
	struct LIBSWBF2_API StreamInfo : public SoundBaseChunk<"Info"_fnv>
	{
		FNVHash m_Name;
		FNVHash m_Format;
		uint32_t m_NumSegments;
		uint32_t m_NumChannels;
		uint32_t m_CombinedSoundSize;

		List<Types::SoundClip> m_SoundHeaders; //TODO: make a separate type for SoundHeaders in bnk/emo_


		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}