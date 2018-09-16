#include "stdafx.h"
#include "GEOM.h"

namespace LibSWBF2::Chunks::Mesh
{
	GEOM::GEOM()
	{

	}

	GEOM::~GEOM()
	{

	}

	void GEOM::RefreshSize()
	{
		/*name.RefreshSize();
		fram.RefreshSize();
		bbox.RefreshSize();

		Size = name.GetSize() + fram.GetSize() + bbox.GetSize();*/
	}

	void GEOM::WriteToStream(FileWriter& stream)
	{
		/*BaseChunk::WriteToStream(stream);
		name.WriteToStream(stream);
		fram.WriteToStream(stream);
		bbox.WriteToStream(stream);*/
	}

	void GEOM::ReadFromStream(FileReader& stream)
	{
		/*BaseChunk::ReadFromStream(stream);
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
		}*/
	}
}