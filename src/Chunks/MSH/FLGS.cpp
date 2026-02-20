#include <LibSWBF2/pch.h>
#include <LibSWBF2/Chunks/MSH/FLGS.h>
#include <LibSWBF2/IO/FileReader.h>
#include <LibSWBF2/IO/FileWriter.h>

namespace LibSWBF2::Chunks::MSH
{
	void FLGS::RefreshSize()
	{
		m_Size = sizeof(uint32_t);
	}

	void FLGS::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteUInt32(m_ModelDisplayFlags);
	}

	void FLGS::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		m_ModelDisplayFlags = stream.ReadUInt32();
		BaseChunk::EnsureEnd(stream);
	}
}