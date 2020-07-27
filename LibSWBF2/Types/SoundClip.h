#pragma once

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

		// Header
		FNVHash m_NameHash;
		uint32_t m_SampleRate;
		uint32_t m_SampleCount;
		uint32_t m_DataLength;

		const uint8_t* GetSampleData() const;
		uint8_t GetBytesPerSample() const;

		// returns size of read header
		uint8_t ReadHeaderFromStream(FileReader& stream);

		void ReadDataFromStream(FileReader& stream);

		String ToString();

	private:
		uint8_t* m_Data;
	};
}