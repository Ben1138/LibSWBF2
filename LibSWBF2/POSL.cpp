#include "stdafx.h"
#include "POSL.h"

namespace LibSWBF2::Chunks::Mesh
{
	void POSL::RefreshSize()
	{
		m_Size = (ChunkSize)(sizeof(uint32_t) + m_Vertices.size() * Vector3::SIZE);
	}

	void POSL::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteUInt32((uint32_t)m_Vertices.size());

		for (size_t i = 0; i < m_Vertices.size(); ++i)
		{
			m_Vertices[i].WriteToStream(stream);
		}
	}

	void POSL::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		uint32_t numVertices = stream.ReadUInt32();

		m_Vertices.clear();
		m_Vertices.reserve(numVertices);

		for (uint32_t i = 0; i < numVertices; ++i)
		{
			Vector3& vertex = m_Vertices.emplace_back();
			vertex.ReadFromStream(stream);
		}

		BaseChunk::EnsureEnd(stream);
	}
}