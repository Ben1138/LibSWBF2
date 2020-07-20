#pragma once
#include "List.h"
#include "SoundClip.h"

namespace LibSWBF2
{
	class FileReader;
	class FileWriter;
}

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API SoundBankHeader
	{
		SoundBankHeader() = default;
		~SoundBankHeader() = default;

		FNVHash m_NameHash;
		uint32_t m_NumClips;
		uint32_t m_DataSize;		// size of all samples from all clips

		List<SoundClip> m_Clips;

		// will set stream head to end position of header (inclusive filling zeros)
		void ReadFromStream(FileReader& stream);

		bool TryLookupName(String& result);
		String ToString();
	};
}