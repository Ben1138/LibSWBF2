#include "stdafx.h"
#include "FRAM.h"

namespace LibSWBF2::Chunks::MSH
{
	FRAM::FRAM()
	{

	}

	FRAM::~FRAM()
	{

	}

	void FRAM::WriteToStream(ofstream& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream << FrameRangeStart;
		stream << FrameRangeEnd;
		stream << FramesPerSecond;
	}

	void FRAM::ReadFromStream(ifstream& stream)
	{
		BaseChunk::ReadFromStream(stream);
		stream >> FrameRangeStart;
		stream >> FrameRangeEnd;
		stream >> FramesPerSecond;
	}
}