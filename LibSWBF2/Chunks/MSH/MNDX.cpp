#include "stdafx.h"
#include "MNDX.h"

namespace LibSWBF2::Chunks::MSH
{
	void MNDX::RefreshSize()
	{
		m_Size = sizeof(uint32_t);
	}

	void MNDX::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteUInt32(m_ModelIndex);
	}

	void MNDX::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		m_ModelIndex = stream.ReadUInt32();
		BaseChunk::EnsureEnd(stream);
	}
}