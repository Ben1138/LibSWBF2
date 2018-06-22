#include "stdafx.h"
#include "SHVO.h"

namespace LibSWBF2
{
	SHVO::SHVO()
	{

	}

	SHVO::~SHVO()
	{

	}

	void SHVO::WriteToStream(ofstream& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream << ShadowVolume;
	}

	void SHVO::ReadFromStream(ifstream& stream)
	{
		BaseChunk::ReadFromStream(stream);
		stream >> ShadowVolume;
	}

	ofstream& operator<<(ofstream& stream, SHVO& chunk)
	{
		chunk.WriteToStream(stream);
	}

	ifstream& operator>>(ifstream& stream, SHVO& chunk)
	{
		chunk.ReadFromStream(stream);
	}
}