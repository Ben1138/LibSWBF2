#include "stdafx.h"
#include "FRAM.h"

namespace LibSWBF2::Chunks::Mesh
{
	void FRAM::RefreshSize()
	{
		m_Size = sizeof(int32_t) + sizeof(int32_t) + sizeof(float_t);
	}

	void FRAM::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteInt32(m_FrameRangeStart);
		stream.WriteInt32(m_FrameRangeEnd);
		stream.WriteFloat(m_FramesPerSecond);
	}

	void FRAM::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		m_FrameRangeStart = stream.ReadInt32();
		m_FrameRangeEnd = stream.ReadInt32();
		m_FramesPerSecond = stream.ReadFloat();
		BaseChunk::EnsureEnd(stream);
	}
}