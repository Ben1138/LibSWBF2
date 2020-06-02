#include "stdafx.h"
#include "FLGS.h"

namespace LibSWBF2::Chunks::MSH
{
	void FLGS::RefreshSize()
	{
		m_Size = sizeof(uint32_t);
	}

	void FLGS::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteUInt32(m_ModelDisplayFlags);
	}

	void FLGS::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		m_ModelDisplayFlags = stream.ReadUInt32();
		BaseChunk::EnsureEnd(stream);
	}
}