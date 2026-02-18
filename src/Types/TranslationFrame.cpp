#include <LibSWBF2/pch.h>
#include <LibSWBF2/Types/TranslationFrame.h>
#include <LibSWBF2/IO/FileWriter.h>
#include <LibSWBF2/IO/FileReader.h>

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