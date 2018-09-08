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

		// sadly, switch-case is not possible here (Error C2051)
		if (head == HeaderNames::SHVO)
		{
			shvo.ReadFromStream(stream);
		}
		else if (head == HeaderNames::MSH2)
		{
			msh2.ReadFromStream(stream);
		}
		else
		{
			Log("Unknown Chunk found: " + HeaderNames::GetHeaderString(head), ELogType::Warning);
		}
	}
}