#include "stdafx.h"
#include "POSL.h"

namespace LibSWBF2::Chunks::MSH
{
	void POSL::RefreshSize()
	{
		m_Size = (ChunkSize)(sizeof(uint32_t) + m_Vertices.Size() * Vector3::SIZE);
	}

	void POSL::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteUInt32((uint32_t)m_Vertices.Size());

		for (size_t i = 0; i < m_Vertices.Size(); ++i)
		{
			m_Vertices[i].WriteToStream(stream);
		}
	}

	void POSL::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		uint32_t numVertices = stream.ReadUInt32();

		m_Vertices.Clear();
		m_Vertices.Resize(numVertices);

		for (uint32_t i = 0; i < numVertices; ++i)
		{
			Vector3& vertex = m_Vertices.Emplace();
			vertex.ReadFromStream(stream);
		}

		BaseChunk::EnsureEnd(stream);
	}
}