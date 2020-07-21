#include "stdafx.h"
#include "SEGM.h"
#include "FileReader.h"
#include "FileWriter.h"

namespace LibSWBF2::Chunks::MSH
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
			m_MaterialIndex.GetDataSize() +
			m_VertexList.GetDataSize() +
			m_WeightList.GetDataSize() +
			m_NormalList.GetDataSize() +
			m_UVList.GetDataSize() +
			m_TriangleList.GetDataSize();
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

		while (ThereIsAnother(stream))
		{
			ChunkHeader head = stream.ReadChunkHeader(true);

			if (head == "MATI"_h)
			{
				m_MaterialIndex.ReadFromStream(stream);
			}
			else if (head == "POSL"_h)
			{
				m_VertexList.ReadFromStream(stream);
			}
			else if (head == "WGHT"_h)
			{
				m_WeightList.ReadFromStream(stream);
			}
			else if (head == "NRML"_h)
			{
				m_NormalList.ReadFromStream(stream);
			}
			else if (head == "UV0L"_h)
			{
				m_UVList.ReadFromStream(stream);
			}
			else if (head == "STRP"_h)
			{
				m_TriangleList.ReadFromStream(stream);
			}
			else if (head == "CLRL"_h || head == "CLRB"_h ||
					 head == "NDXL"_h || head == "NDXT"_h)
			{
				// CLRL and CLRB are not supported
				// NDXL and NDXT are deprecated and thus not supported
				SkipChunk(stream, false);
			}
			else
			{
				SkipChunk(stream);
			}
		}

		BaseChunk::EnsureEnd(stream);
	}
}