#include "stdafx.h"
#include "SEGM.h"

namespace LibSWBF2::Chunks::Mesh
{
	SEGM::SEGM()
	{

	}

	SEGM::~SEGM()
	{

	}

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
		m_MaterialIndex.ReadFromStream(stream);
		m_VertexList.ReadFromStream(stream);
		m_WeightList.ReadFromStream(stream);
		m_NormalList.ReadFromStream(stream);
		m_UVList.ReadFromStream(stream);
		m_TriangleList.ReadFromStream(stream);
	}
}