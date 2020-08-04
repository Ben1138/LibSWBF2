#include "stdafx.h"
#include "lght.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::light
{
	void lght::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void lght::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void lght::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		READ_CHILD(stream, p_Name);
		READ_CHILD(stream, p_Info);

		while (ThereIsAnother(stream))
		{
			FMT_* fmt;
			READ_CHILD(stream, fmt);
			m_FMTs.Add(fmt);
		}

		BaseChunk::EnsureEnd(stream);
	}

	String lght::ToString()
	{
		return fmt::format(
			"Number of lights: {}",
			m_Lights.Size()
		).c_str();
	}
}
