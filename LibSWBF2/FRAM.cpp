#include "stdafx.h"
#include "FRAM.h"

namespace LibSWBF2::Chunks::Mesh
{
	FRAM::FRAM()
	{

	}

	FRAM::~FRAM()
	{

	}

	void FRAM::RefreshSize()
	{
		Size = sizeof(int32_t) + sizeof(int32_t) + sizeof(float_t);
	}

	void FRAM::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteInt32(FrameRangeStart);
		stream.WriteInt32(FrameRangeEnd);
		stream.WriteFloat(FramesPerSecond);
	}

	void FRAM::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		FrameRangeStart = stream.ReadInt32();
		FrameRangeEnd = stream.ReadInt32();
		FramesPerSecond = stream.ReadFloat();
	}
}