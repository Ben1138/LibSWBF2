#include "pch.h"
#include "Stream.h"
#include "StreamInfo.h"
#include "StreamData.h"
#include "InternalHelpers.h"
#include "FileReader.h"


namespace LibSWBF2::Chunks::LVL::sound
{
	FNVHash Stream::PeekStreamName(FileReader& stream)
	{
		size_t OriginalPosition = stream.GetPosition();

		FNVHash result = 0;

		if (stream.CheckGood(20))
		{
			stream.SkipBytes(20);
			result = stream.ReadUInt32();
		}

		stream.SetPosition(OriginalPosition);

		return result;
	}



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
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		while (ThereIsAnother(stream))
		{
			ChunkHeader next = stream.ReadChunkHeader(true);
			if (next == "Info"_fnvh)
			{
				READ_CHILD(stream, p_Info);
			}
			else if (next == "Data"_fnvh)
			{
				READ_CHILD(stream, p_Data);
				if (!PositionInChunk(stream.GetPosition()))
				{
					stream.SetPosition(GetDataPosition() + GetAlignedSize());
					break;
				}
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
		return p_Info == nullptr ? "No info chunk found..." : p_Info -> HeaderToString();
	}
}