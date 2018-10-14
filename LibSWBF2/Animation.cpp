#include "stdafx.h"
#include "Animation.h"

namespace LibSWBF2::Types
{
	void Animation::WriteToStream(FileWriter& stream)
	{
		stream.WriteString(m_AnimationName, ANIMATION_NAME_STR_SIZE);
		stream.WriteFloat(m_FrameRate);
		stream.WriteUInt32(m_PlayStyle);
		stream.WriteUInt32(m_FirstFrame);
		stream.WriteUInt32(m_LastFrame);
	}

	void Animation::ReadFromStream(FileReader& stream)
	{
		m_AnimationName = stream.ReadString(ANIMATION_NAME_STR_SIZE);
		m_FrameRate = stream.ReadFloat();
		m_PlayStyle = stream.ReadUInt32();
		m_FirstFrame = stream.ReadUInt32();
		m_LastFrame = stream.ReadUInt32();
	}
}