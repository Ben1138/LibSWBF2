#pragma once
#include "SoundClip.h"
#include "List.h"

namespace LibSWBF2
{
	class FileReader;
	class FileWriter;
}

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API SoundBank
	{
		SoundBank() = default;
		~SoundBank() = default;

		FNVHash m_NameHash;
		uint32_t m_NumClips;

		// size of all samples from all clips
		uint32_t m_DataSize;

		List<SoundClip> m_Clips;

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		String ToString();
	};
}