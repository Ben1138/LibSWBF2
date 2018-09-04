#include "stdafx.h"
#include "MSH.h"

namespace LibSWBF2::Chunks::MSH
{
	MSH::MSH()
	{

	}

	MSH::~MSH()
	{

	}

	void MSH::RefreshSize()
	{
		shvo.RefreshSize();

		Size = shvo.GetSize();
	}

	void MSH::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		shvo.WriteToStream(stream);
	}

	void MSH::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		ChunkHeader head = stream.ReadChunkHeader(true);

		if (head == HeaderNames::SHVO)
			shvo.ReadFromStream(stream);
	}
}