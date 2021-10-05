#include "pch.h"
#include "_pad.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::sound
{
	void _pad::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void _pad::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void _pad::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		// for some reason, they don't write any data size
		// TODO: if WriteToStream is ever implemented, make
		// sure to write also 0 as size back!

		m_Unknown1 = stream.ReadUInt32();
		m_Unknown2 = stream.ReadUInt32();

		BaseChunk::EnsureEnd(stream);
	}

	String _pad::ToString() const
	{
		return fmt::format(
			"Unknown 1: {}\n"
			"Unknown 2: {}",
			m_Unknown1,
			m_Unknown2
		).c_str();
	}
}