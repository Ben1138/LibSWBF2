#include "stdafx.h"
#include "GEOM.h"

namespace LibSWBF2::Chunks::Mesh
{
	void GEOM::RefreshSize()
	{
		m_BoundingBox.RefreshSize();
		m_Envelope.RefreshSize();
		m_Size = m_BoundingBox.GetSize() + m_Envelope.GetSize();

		for (size_t i = 0; i < m_Segments.size(); ++i)
		{
			m_Segments[i].RefreshSize();
			m_Size += m_BoundingBox.GetSize();
		}
	}

	void GEOM::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_BoundingBox.WriteToStream(stream);

		for (size_t i = 0; i < m_Segments.size(); ++i)
		{
			m_Segments[i].WriteToStream(stream);
		}

		m_Envelope.WriteToStream(stream);
	}

	void GEOM::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);

		while (PositionInChunk(stream.GetPosition()))
		{
			ChunkHeader head = stream.ReadChunkHeader(true);

			if (head == HeaderNames::BBOX)
			{
				m_BoundingBox.ReadFromStream(stream);
			}
			else if (head == HeaderNames::SEGM)
			{
				SEGM& segment = m_Segments.emplace_back();
				segment.ReadFromStream(stream);
			}
			else if (head == HeaderNames::ENVL)
			{
				m_Envelope.ReadFromStream(stream);
			}
			else
			{
				SkipChunk(stream);
			}
		}

		BaseChunk::EnsureEnd(stream);
	}
}