#include "stdafx.h"
#include "NAME.h"

namespace LibSWBF2::Chunks::Mesh
{
	NAME::NAME()
	{

	}

	NAME::~NAME()
	{

	}

	void NAME::RefreshSize()
	{
		// size must be a multiple of 4
		m_Size = (ChunkSize)m_Text.size();
		m_Size += 4 - (m_Size % 4);
	}

	void NAME::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteString(m_Text, m_Size);
	}

	void NAME::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		m_Text = stream.ReadString(m_Size);
	}
}