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
}