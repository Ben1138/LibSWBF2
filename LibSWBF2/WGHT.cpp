#include "stdafx.h"
#include "WGHT.h"

namespace LibSWBF2::Chunks::Mesh
{
	void WGHT::RefreshSize()
	{
		m_Size = (ChunkSize)(m_Weights.size() * BoneWeight::SIZE);
	}

	void WGHT::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteUInt32((uint32_t)m_Weights.size());

		for (size_t i = 0; i < m_Weights.size(); ++i)
		{
			m_Weights[i][0].WriteToStream(stream);
			m_Weights[i][1].WriteToStream(stream);
			m_Weights[i][2].WriteToStream(stream);
			m_Weights[i][3].WriteToStream(stream);
		}
	}

	void WGHT::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		uint32_t WeightSize = stream.ReadUInt32();

		m_Weights.clear();
		m_Weights.reserve(WeightSize);

		for (uint32_t i = 0; i < WeightSize; ++i)
		{
			array<BoneWeight, 4>& weight = m_Weights.emplace_back();
			weight[0].ReadFromStream(stream);
			weight[1].ReadFromStream(stream);
			weight[2].ReadFromStream(stream);
			weight[3].ReadFromStream(stream);
		}

		BaseChunk::EnsureEnd(stream);
	}
}