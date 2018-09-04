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
		Size = sizeof(int32_t);
	}

	void SHVO::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteInt32(ShadowVolume);
	}

	void SHVO::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		ShadowVolume = stream.ReadInt32();
	}
}