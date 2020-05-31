#include "stdafx.h"
#include "STR.h"

namespace LibSWBF2::Chunks
{
	void STR::RefreshSize()
	{
		// size must be a multiple of 4
		m_Size = (ChunkSize)m_Text.Length();
	}

	void STR::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteString(m_Text, true);
	}

	void STR::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		m_Text = stream.ReadString(m_Size);
		BaseChunk::EnsureEnd(stream);
	}

	String STR::ToString()
	{
		return m_Text;
	}
}