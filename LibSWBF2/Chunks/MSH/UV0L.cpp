#include "stdafx.h"
#include "UV0L.h"

namespace LibSWBF2::Chunks::MSH
{
	void UV0L::RefreshSize()
	{
		m_Size = (ChunkSize)(sizeof(uint32_t) + m_UVs.Size() * Vector2::SIZE);
	}

	void UV0L::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteUInt32((uint32_t)m_UVs.Size());

		for (size_t i = 0; i < m_UVs.Size(); ++i)
		{
			m_UVs[i].WriteToStream(stream);
		}
	}

	void UV0L::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		uint32_t numVertices = stream.ReadUInt32();

		m_UVs.Clear();
		m_UVs.Resize(numVertices);

		for (uint32_t i = 0; i < numVertices; ++i)
		{
			Vector2& uv = m_UVs.Emplace();
			uv.ReadFromStream(stream);
		}

		BaseChunk::EnsureEnd(stream);
	}
}