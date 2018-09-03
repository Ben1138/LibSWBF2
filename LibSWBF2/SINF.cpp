#include "stdafx.h"
#include "SINF.h"

namespace LibSWBF2::Chunks::MSH
{
	SINF::SINF()
	{

	}

	SINF::~SINF()
	{

	}

	void SINF::RefreshSize()
	{
		// TODO: proper implementation
		Size = 0;
	}

	void SINF::WriteToStream(ofstream& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream << ShadowVolume;
	}

	void SINF::ReadFromStream(ifstream& stream)
	{
		BaseChunk::ReadFromStream(stream);
		stream >> ShadowVolume;
	}
}