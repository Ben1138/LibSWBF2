#include "pch.h"
#include "StreamList.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::sound
{
	void StreamList::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void StreamList::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void StreamList::ReadFromStream(FileReader& stream)
	{
		SoundBaseChunk::ReadFromStream(stream);
		Check(stream);

		while (ThereIsAnother(stream))
		{
			if (stream.ReadChunkHeader(true) == "snd_"_h)
			{
				READ_CHILD_GENERIC(stream);
			}
			else if (stream.ReadChunkHeader(false) == "emo_"_h)
			{
				m_NumStreams++;
			}		
		}

		BaseChunk::EnsureEnd(stream);
	}

	String StreamList::ToString() const
	{
		std::string result = fmt::format(
			"{0}\nNum streams: {1}",
			SoundBaseChunk::ToString().Buffer(),
			m_NumStreams
		);

		return result.c_str();
	}
}