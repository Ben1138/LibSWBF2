#include "stdafx.h"
#include "MNDX.h"

namespace LibSWBF2::Chunks::MSH
{
	MNDX::MNDX()
	{

	}

	MNDX::~MNDX()
	{

	}

	void MNDX::RefreshSize()
	{
		Size = sizeof(uint32_t);
	}

	void MNDX::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteUInt32(ModelIndex);
	}

	void MNDX::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		ModelIndex = stream.ReadUInt32();
	}
}