#include "stdafx.h"
#include "SWCI.h"

namespace LibSWBF2::Chunks::MSH
{
	void SWCI::RefreshSize()
	{
		m_Size = sizeof(uint32_t) + Vector3::SIZE;
	}

	void SWCI::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteUInt32((uint32_t)m_PrimitiveType);
		m_Dimensions.WriteToStream(stream);
	}

	void SWCI::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		m_PrimitiveType = (ECollisionPrimitive)stream.ReadUInt32();
		m_Dimensions.ReadFromStream(stream);
		BaseChunk::EnsureEnd(stream);
	}
}