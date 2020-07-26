#include "stdafx.h"
#include "Types/LibString.h"
#include "SoundBank.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "InternalHelpers.h"

namespace LibSWBF2::Types
{
	void SoundBank::WriteToStream(FileWriter& stream)
	{
		THROW("Not Implemented!");
	}

	void SoundBank::ReadFromStream(FileReader& stream)
	{
		// Bank header size is exactly 74 bytes, most of it yet unknown
		// right after the bank header come the individual clip headers,
		// which are 48 bytes each. The sample data starts at position 2048,
		// which means there's space for up to 40 clip headers.
		// The remain is filled with zeros.

		stream.SkipBytes(28);
		m_NameHash = stream.ReadUInt32();
		stream.SkipBytes(12);
		m_NumClips = stream.ReadUInt32();
		stream.SkipBytes(4);
		m_DataSize = stream.ReadUInt32();
		stream.SkipBytes(18);

		for (uint32_t i = 0; i < m_NumClips; ++i)
		{
			m_Clips.Emplace().ReadHeaderFromStream(stream);
		}



		// sample data stream starts at a multiple of 2048, depending on
		// how many clip headers (again, each with 48 bytes) there are
		size_t sampleDataOffset = (size_t)std::ceil(m_NumClips * 48.0f / 2048.0f);
		stream.SetPosition(sampleDataOffset);
	}

	String SoundBank::ToString()
	{
		std::string result = fmt::format(
			"Name Hash: {}\n"
			"Data Size: {}\n"
			"Clip Count: {}\n",
			m_NameHash,
			m_DataSize,
			m_Clips.Size()
		);

		result += "\n";
		for (size_t i = 0; i < m_Clips.Size(); ++i)
		{
			result += fmt::format("Clip {}:\n{}\n", i, m_Clips[i].ToString());
		}

		return result.c_str();
	}
}