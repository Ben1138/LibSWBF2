#include "pch.h"
#include "emo_.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::sound
{
	void emo_::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void emo_::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void emo_::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		size_t bankPos = stream.GetPosition() - 8;

		// Bank header size in emo_ is exactly 82 bytes, most of it yet unknown
		// right after the bank header come the individual clip headers,
		// which are 48 or 56 bytes each.

		stream.SkipBytes(44);
		m_NumClips = stream.ReadUInt32();
		stream.SkipBytes(34);

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
		// how much space the clip headers take
		size_t sampleDataOffset = (size_t)std::ceil((bankPos + headersSize) / 2048.0f) * 2048;
		stream.SetPosition(sampleDataOffset);

		uint32_t i = 0;
		try
		{
			for (i = 0; i < m_Clips.Size(); ++i)
			{
				m_Clips[i].ReadDataFromStream(stream);
			}
		}
		catch (LibException& e)
		{
			LOG_ERROR(e.what());
		}

		BaseChunk::EnsureEnd(stream);
	}

	String emo_::ToString() const
	{
		std::string result = fmt::format(
			"Clip Count: {}\n",
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