#pragma once
#include "Types/LibString.h"

namespace LibSWBF2
{
	class FileReader;
	class FileWriter;
}

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API SoundClip
	{
		SoundClip();
		~SoundClip();

		size_t m_HeaderPosition;
		size_t m_DataPosition;

		// Header
		FNVHash m_NameHash;
		uint32_t m_SampleRate;
		uint32_t m_SampleCount;
		uint32_t m_DataLength;
		uint32_t m_Padding;
		uint32_t m_Alias;

		const uint8_t* GetSampleData() const;
		uint8_t GetBytesPerSample() const;

		// returns size of read header
		uint8_t ReadHeaderFromStream(FileReader& stream);
		void ReadDataFromStream(FileReader& stream);

		bool TryLookupName(String& result);
		String ToString() const;

	private:
		uint8_t* m_Data = nullptr;
	};
}