#include "stdafx.h"
#include "MATL.h"

namespace LibSWBF2::Chunks::Mesh
{
	void MATL::RefreshSize()
	{
		ChunkSize matChunksSize = 0;
		for (size_t i = 0; i < m_Materials.Size(); ++i)
		{
			m_Materials[i].RefreshSize();
			matChunksSize += m_Materials[i].GetDataSize();
		}

		m_Size = sizeof(uint32_t) + matChunksSize;
	}

	void MATL::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteUInt32((uint32_t)m_Materials.Size());

		for (size_t i = 0; i < m_Materials.Size(); ++i)
		{
			m_Materials[i].WriteToStream(stream);
		}
	}

	void MATL::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		uint32_t MaterialsSize = stream.ReadUInt32();

		m_Materials.Clear();
		m_Materials.Resize(MaterialsSize);

		for (uint32_t i = 0; i < MaterialsSize; ++i)
		{
			MATD& material = m_Materials.Emplace();
			material.ReadFromStream(stream);
		}

		BaseChunk::EnsureEnd(stream);
	}
}