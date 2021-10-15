#include "pch.h"
#include "Stream.h"
#include "StreamInfo.h"
#include "SoundBaseChunk.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::sound
{
	void Stream::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void Stream::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void Stream::ReadFromStream(FileReader& stream)
	{
		SoundBaseChunk::ReadFromStream(stream);
		Check(stream);

		while (ThereIsAnother(stream))
		{
			ChunkHeader next = stream.ReadChunkHeader(true);
			if (next == "Info"_fnvh)
			{
				READ_CHILD(stream, p_Info);
			}
			else 
			{
				stream.SkipBytes(4);
			}
		}

		BaseChunk::EnsureEnd(stream);
	}

	String Stream::ToString() const
	{
		std::string result = fmt::format(
			"{0}\n{1}",
			SoundBaseChunk::ToString().Buffer(),
			p_Info == nullptr ? "No info chunk found" : p_Info -> ToString().Buffer()
		);

		return result.c_str();
	}
}