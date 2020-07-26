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
		uint32_t m_SmaplesCount;
		uint32_t m_DataLength;

		uint8_t* GetSampleData() const;
		void ReadHeaderFromStream(FileReader& stream);
		void ReadDataFromStream(FileReader& stream);

		String ToString();

	private:
		uint8_t* m_Data;
	};
}