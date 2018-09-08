#include "stdafx.h"
#include "MTYP.h"

namespace LibSWBF2::Chunks::MSH
{
	MTYP::MTYP()
	{

	}

	MTYP::~MTYP()
	{

	}

	void MTYP::RefreshSize()
	{
		Size = sizeof(uint32_t);
	}

	void MTYP::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteUInt32(ModelType);
	}

	void MTYP::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		ModelType = (EModelType)stream.ReadUInt32();
	}
}