#include "stdafx.h"
#include "SHVO.h"

namespace LibSWBF2::Chunks::MSH
{
	SHVO::SHVO()
	{

	}

	SHVO::~SHVO()
	{

	}

	void SHVO::RefreshSize()
	{
		// TODO: proper implementation
		Size = 0;
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
}