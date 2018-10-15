#include "stdafx.h"
#include "SEGM.h"

namespace LibSWBF2::Chunks::Mesh
{
	void SEGM::RefreshSize()
	{
		m_MaterialIndex.RefreshSize();
		m_VertexList.RefreshSize();
		m_WeightList.RefreshSize();
		m_NormalList.RefreshSize();
		m_UVList.RefreshSize();
		m_TriangleList.RefreshSize();

		m_Size =
			m_MaterialIndex.GetSize() +
			m_VertexList.GetSize() +
			m_WeightList.GetSize() +
			m_NormalList.GetSize() +
			m_UVList.GetSize() +
			m_TriangleList.GetSize();
	}

	void SEGM::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_MaterialIndex.WriteToStream(stream);
		m_VertexList.WriteToStream(stream);
		m_WeightList.WriteToStream(stream);
		m_NormalList.WriteToStream(stream);
		m_UVList.WriteToStream(stream);
		m_TriangleList.WriteToStream(stream);
	}

	void SEGM::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);

		while (PositionInChunk(stream.GetPosition()))
		{
			ChunkHeader head = stream.ReadChunkHeader(true);

			if (head == HeaderNames::MATI)
			{
				m_MaterialIndex.ReadFromStream(stream);
			}
			else if (head == HeaderNames::POSL)
			{
				m_VertexList.ReadFromStream(stream);
			}
			else if (head == HeaderNames::WGHT)
			{
				m_WeightList.ReadFromStream(stream);
			}
			else if (head == HeaderNames::NRML)
			{
				m_NormalList.ReadFromStream(stream);
			}
			else if (head == HeaderNames::UV0L)
			{
				m_UVList.ReadFromStream(stream);
			}
			else if (head == HeaderNames::STRP)
			{
				m_TriangleList.ReadFromStream(stream);
			}
			else if (head == HeaderNames::NDXL || head == HeaderNames::NDXT)
			{
				// NDXL and NDXT are deprecated and thus not supported
				continue;
			}
			else
			{
				UnexpectedChunk(stream);
			}
		}

		BaseChunk::EnsureEnd(stream);
	}
}