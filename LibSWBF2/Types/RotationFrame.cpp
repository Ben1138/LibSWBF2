#include "stdafx.h"
#include "RotationFrame.h"
#include "FileWriter.h"
#include "FileReader.h"

namespace LibSWBF2::Types
{
	void RotationFrame::WriteToStream(FileWriter& stream)
	{
		stream.WriteUInt32(m_FrameIndex);
		m_Rotation.WriteToStream(stream);
	}

	void RotationFrame::ReadFromStream(FileReader& stream)
	{
		m_FrameIndex = stream.ReadUInt32();
		m_Rotation.ReadFromStream(stream);
	}
}