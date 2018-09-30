#include "stdafx.h"
#include "MATI.h"

namespace LibSWBF2::Chunks::Mesh
{
	MATI::MATI()
	{

	}

	MATI::~MATI()
	{

	}

	void MATI::RefreshSize()
	{
		m_Size = sizeof(int32_t);
	}

	void MATI::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteInt32(m_MaterialIndex);
	}

	void MATI::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		m_MaterialIndex = stream.ReadInt32();
	}
}