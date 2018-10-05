#include "stdafx.h"
#include "STRING.h"

namespace LibSWBF2::Chunks::Mesh
{
	STRING::STRING()
	{

	}

	STRING::~STRING()
	{

	}

	void STRING::RefreshSize()
	{
		// size must be a multiple of 4
		m_Size = (ChunkSize)m_Text.size();
		m_Size += 4 - (m_Size % 4);
	}

	void STRING::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteString(m_Text, true);
	}

	void STRING::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		m_Text = stream.ReadString(m_Size);
		BaseChunk::EnsureEnd(stream);
	}
}