#include "stdafx.h"
#include "MSH2.h"

namespace LibSWBF2::Chunks::MSH
{
	MSH2::MSH2()
	{

	}

	MSH2::~MSH2()
	{

	}

	void MSH2::WriteToStream(ofstream& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream << ShadowVolume;
	}

	void MSH2::ReadFromStream(ifstream& stream)
	{
		BaseChunk::ReadFromStream(stream);
		stream >> ShadowVolume;
	}
}