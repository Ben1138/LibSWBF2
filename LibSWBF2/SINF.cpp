#include "stdafx.h"
#include "SINF.h"

namespace LibSWBF2::Chunks::Mesh
{
	SINF::SINF()
	{

	}

	SINF::~SINF()
	{

	}

	void SINF::RefreshSize()
	{
		m_NAME.RefreshSize();
		m_FRAM.RefreshSize();
		m_BBOX.RefreshSize();

		m_Size = m_NAME.GetSize() + m_FRAM.GetSize() + m_BBOX.GetSize();
	}

	void SINF::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_NAME.WriteToStream(stream);
		m_FRAM.WriteToStream(stream);
		m_BBOX.WriteToStream(stream);
	}

	void SINF::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		ChunkHeader head = stream.ReadChunkHeader(true);

		if (head == HeaderNames::NAME)
		{
			m_NAME.ReadFromStream(stream);
		}
		else if (head == HeaderNames::FRAM)
		{
			m_FRAM.ReadFromStream(stream);
		}
		else if (head == HeaderNames::BBOX)
		{
			m_BBOX.ReadFromStream(stream);
		}
		else
		{
			Log("Unknown Chunk found: " + HeaderNames::GetHeaderString(head), ELogType::Warning);
		}
	}
}