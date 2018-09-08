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
		name.RefreshSize();
		fram.RefreshSize();
		bbox.RefreshSize();

		Size = name.GetSize() + fram.GetSize() + bbox.GetSize();
	}

	void SINF::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		name.WriteToStream(stream);
		fram.WriteToStream(stream);
		bbox.WriteToStream(stream);
	}

	void SINF::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		ChunkHeader head = stream.ReadChunkHeader(true);

		if (head == HeaderNames::NAME)
		{
			name.ReadFromStream(stream);
		}
		else if (head == HeaderNames::FRAM)
		{
			fram.ReadFromStream(stream);
		}
		else if (head == HeaderNames::BBOX)
		{
			bbox.ReadFromStream(stream);
		}
		else
		{
			Log("Unknown Chunk found: " + HeaderNames::GetHeaderString(head), ELogType::Warning);
		}
	}
}