#include "stdafx.h"
#include "scr_.INFO.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::script
{
	void INFO::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void INFO::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void INFO::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		m_NumBodies = stream.ReadUInt32();

		BaseChunk::EnsureEnd(stream);
	}

	String INFO::ToString() const
	{
		return fmt::format(
			"Num Bodies: {}",
			m_NumBodies
		).c_str();
	}
}