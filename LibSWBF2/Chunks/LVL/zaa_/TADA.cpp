#include "stdafx.h"
#include "TADA.h"
#include "BIN_.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	void TADA::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void TADA::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}


	void TADA::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		//Temp solution, size would explode if this chunk
		//stored proper frame structs
		m_DataBufferLength = GetDataSize();
		p_DataBuffer = new uint8_t[m_DataBufferLength];
		stream.ReadBytes(p_DataBuffer, m_DataBufferLength);

		BaseChunk::EnsureEnd(stream);
	}

	String TADA::ToString()
	{
		return fmt::format("Buffer length = {}", m_DataBufferLength).c_str();
	}

	TADA::~TADA()
	{
		delete[] p_DataBuffer;
	}
}