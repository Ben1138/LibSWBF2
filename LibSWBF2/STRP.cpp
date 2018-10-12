#include "stdafx.h"
#include "STRP.h"

namespace LibSWBF2::Chunks::Mesh
{
	void STRP::RefreshSize()
	{
		m_Size = (ChunkSize)(sizeof(uint32_t) + m_Triangles.size() * sizeof(uint16_t));
	}

	void STRP::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteUInt32((uint32_t)m_Triangles.size());

		for (size_t i = 0; i < m_Triangles.size(); ++i)
		{
			stream.WriteUInt16(m_Triangles[i]);
		}
	}

	void STRP::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		uint32_t numIndices = stream.ReadUInt32();

		m_Triangles.clear();
		m_Triangles.reserve(numIndices);

		for (uint32_t i = 0; i < numIndices; ++i)
		{
			m_Triangles.emplace_back(stream.ReadUInt16());
		}

		BaseChunk::EnsureEnd(stream);
	}
}