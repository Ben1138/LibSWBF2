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

	void MSH2::RefreshSize()
	{
		Size = sizeof(int32_t);
	}

	void MSH2::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteInt32(ShadowVolume);
	}

	void MSH2::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		ShadowVolume = stream.ReadInt32();
	}
}