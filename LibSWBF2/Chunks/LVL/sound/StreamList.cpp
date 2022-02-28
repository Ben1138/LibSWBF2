#include "pch.h"
#include "StreamList.h"
#include "Stream.h"
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
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		while (ThereIsAnother(stream))
		{
			ChunkHeader next = stream.ReadChunkHeader(true);
			if (next == "Stream"_fnvh)
			{
				READ_CHILD(stream, m_Streams.Emplace())
			}
			else 
			{
				stream.SkipBytes(4);
			}		
		}

		BaseChunk::EnsureEnd(stream);
	}

	String StreamList::ToString() const
	{
		std::string result = fmt::format(
			"Num streams: {0}",
			m_Streams.Size()
		);

		return result.c_str();
	}
}