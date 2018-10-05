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
		m_Name.RefreshSize();
		m_FrameInformation.RefreshSize();
		m_BoundingBox.RefreshSize();

		m_Size = m_Name.GetSize() + m_FrameInformation.GetSize() + m_BoundingBox.GetSize();
	}

	void SINF::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_Name.WriteToStream(stream);
		m_FrameInformation.WriteToStream(stream);
		m_BoundingBox.WriteToStream(stream);
	}

	void SINF::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);

		while (PositionInChunk(stream.GetPosition()))
		{
			ChunkHeader head = stream.ReadChunkHeader(true);
		
			if (head == HeaderNames::NAME)
			{
				m_Name.ReadFromStream(stream);
			}
			else if (head == HeaderNames::FRAM)
			{
				m_FrameInformation.ReadFromStream(stream);
			}
			else if (head == HeaderNames::BBOX)
			{
				m_BoundingBox.ReadFromStream(stream);
			}
			else
			{
				UnexpectedChunk(stream);
			}
		}

		BaseChunk::EnsureEnd(stream);
	}
}