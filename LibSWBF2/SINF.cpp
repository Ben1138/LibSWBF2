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

	void SINF::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteInt32(ShadowVolume);
	}

	void SINF::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		ShadowVolume = stream.ReadInt32();
	}
}