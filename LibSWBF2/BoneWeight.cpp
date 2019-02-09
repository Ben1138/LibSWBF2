#include "stdafx.h"
#include "BoneWeight.h"

namespace LibSWBF2::Types
{
	void BoneWeight::WriteToStream(FileWriter& stream)
	{
		stream.WriteUInt32(m_EnvelopeIndex);
		stream.WriteFloat(m_WeightValue);
	}

	void BoneWeight::ReadFromStream(FileReader& stream)
	{
		m_EnvelopeIndex = stream.ReadUInt32();
		m_WeightValue = stream.ReadFloat();
	}

	void VertexWeights::WriteToStream(FileWriter& stream)
	{
		m_BoneWeights[0].WriteToStream(stream);
		m_BoneWeights[1].WriteToStream(stream);
		m_BoneWeights[2].WriteToStream(stream);
		m_BoneWeights[3].WriteToStream(stream);
	}

	void VertexWeights::ReadFromStream(FileReader& stream)
	{
		m_BoneWeights[0].ReadFromStream(stream);
		m_BoneWeights[1].ReadFromStream(stream);
		m_BoneWeights[2].ReadFromStream(stream);
		m_BoneWeights[3].ReadFromStream(stream);
	}
}