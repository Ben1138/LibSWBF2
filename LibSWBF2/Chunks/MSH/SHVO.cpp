#include "stdafx.h"
#include "SHVO.h"

namespace LibSWBF2::Chunks::MSH
{
	void SHVO::RefreshSize()
	{
		m_Size = sizeof(int32_t);
	}

	void SHVO::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteInt32(m_ShadowVolume);
	}

	void SHVO::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		m_ShadowVolume = stream.ReadInt32();
		BaseChunk::EnsureEnd(stream);
	}
}