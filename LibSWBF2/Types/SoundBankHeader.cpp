#include "stdafx.h"
#include "Types/LibString.h"
#include "SoundBankHeader.h"
#include "FileReader.h"
#include "InternalHelpers.h"
#include "Hashing.h"

namespace LibSWBF2::Types
{
	void SoundBankHeader::ReadFromStream(FileReader& stream)
	{
		size_t bankPos = stream.GetPosition() - 8;

		// Bank header size is exactly 74 bytes, most of it yet unknown
		// right after the bank header come the individual clip headers,
		// which are 48 or 56 bytes each.

		stream.SkipBytes(28);
		m_NameHash = stream.ReadUInt32();
		stream.SkipBytes(12);
		m_NumClips = stream.ReadUInt32();
		stream.SkipBytes(4);
		m_DataSize = stream.ReadUInt32();
		stream.SkipBytes(18);

		size_t headersSize = 0;
		for (uint32_t i = 0; i < m_NumClips; ++i)
		{
			headersSize += m_Clips.Emplace().ReadHeaderFromStream(stream);
		}

		if (m_Clips.Size() != m_NumClips)
		{
			LOG_WARN("Expected {} sound clip headers, but read {}!", m_NumClips, m_Clips.Size());
		}

		// sample data stream starts at a multiple of 2048, depending on
		// how much space the clip headers take. The rest is filled with zeros
		size_t sampleDataOffset = ((size_t)std::ceil((bankPos + headersSize) / 2048.0f)) * 2048;
		stream.SetPosition(sampleDataOffset);
	}

	bool SoundBankHeader::TryLookupName(String& result)
	{
		return FNV::Lookup(m_NameHash, result);
	}

	String SoundBankHeader::ToString()
	{
		String bankName;
		if (!FNV::Lookup(m_NameHash, bankName))
			bankName = std::to_string(m_NameHash).c_str();

		std::string result = fmt::format(
			"Name: {}\n"
			"Data Size: {}\n"
			"Clip Count: {}\n"
			"Read Clips: {}\n",
			bankName,
			m_DataSize,
			m_NumClips,
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