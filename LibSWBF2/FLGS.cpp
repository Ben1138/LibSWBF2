#include "stdafx.h"
#include "FLGS.h"

namespace LibSWBF2::Chunks::Mesh
{
	FLGS::FLGS()
	{

	}

	FLGS::~FLGS()
	{

	}

	void FLGS::RefreshSize()
	{
		Size = sizeof(uint32_t);
	}

	void FLGS::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteUInt32(ModelDisplayFlags);
	}

	void FLGS::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		ModelDisplayFlags = stream.ReadUInt32();
	}
}