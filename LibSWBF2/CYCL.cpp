#include "stdafx.h"
#include "CYCL.h"

namespace LibSWBF2::Chunks::Mesh
{
	void CYCL::RefreshSize()
	{
		m_Size = sizeof(uint32_t) + sizeof(STRING) + sizeof(float_t) + sizeof(uint32_t) + sizeof(uint32_t) + sizeof(uint32_t);
	}

	void CYCL::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteUInt32(m_NumberOfAnimations);
		stream.WriteString(m_AnimationName);
		stream.WriteFloat(m_FrameRate);
		stream.WriteUInt32(m_PlayStyle);
		stream.WriteUInt32(m_FirstFrame);
		stream.WriteUInt32(m_LastFrame);
	}

	void CYCL::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		m_NumberOfAnimations = stream.ReadUInt32();
		m_AnimationName = stream.ReadString();
		m_FrameRate = stream.ReadFloat();
		m_PlayStyle = stream.ReadUInt32();
		m_FirstFrame = stream.ReadUInt32();
		m_LastFrame = stream.ReadUInt32();
		BaseChunk::EnsureEnd(stream);
	}
}