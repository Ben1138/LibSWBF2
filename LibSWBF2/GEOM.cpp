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
		/*m_NAME.RefreshSize();
		fram.RefreshSize();
		m_BBOX.RefreshSize();

		Size = m_NAME.GetSize() + fram.GetSize() + m_BBOX.GetSize();*/
	}

	void GEOM::WriteToStream(FileWriter& stream)
	{
		/*BaseChunk::WriteToStream(stream);
		m_NAME.WriteToStream(stream);
		fram.WriteToStream(stream);
		m_BBOX.WriteToStream(stream);*/
	}

	void GEOM::ReadFromStream(FileReader& stream)
	{
		/*BaseChunk::ReadFromStream(stream);
		ChunkHeader head = stream.ReadChunkHeader(true);

		if (head == HeaderNames::NAME)
		{
			m_NAME.ReadFromStream(stream);
		}
		else if (head == HeaderNames::FRAM)
		{
			fram.ReadFromStream(stream);
		}
		else if (head == HeaderNames::BBOX)
		{
			m_BBOX.ReadFromStream(stream);
		}
		else
		{
			Log("Unknown Chunk found: " + HeaderNames::GetHeaderString(head), ELogType::Warning);
		}*/
	}
}