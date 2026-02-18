#include <pch.h>
#include <Types/TranslationFrame.h>
#include <IO/FileWriter.h>
#include <IO/FileReader.h>

namespace LibSWBF2::Types
{
	void TranslationFrame::WriteToStream(FileWriter& stream)
	{
		stream.WriteUInt32(m_FrameIndex);
		m_Translation.WriteToStream(stream);
	}

	void TranslationFrame::ReadFromStream(FileReader& stream)
	{
		m_FrameIndex = stream.ReadUInt32();
		m_Translation.ReadFromStream(stream);
	}
}