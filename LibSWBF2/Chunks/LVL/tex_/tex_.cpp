#include "stdafx.h"
#include "tex_.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::texture
{
	void tex_::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void tex_::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void tex_::ReadFromStream(FileReader& stream)
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

	String tex_::ToString() const
	{
		return fmt::format(
			"Name: {}\n\n"
			"Info: {}\n"
			"Number of FMTs: {}",
			p_Name->m_Text,
			p_Info->ToString(),
			m_FMTs.Size()
		).c_str();
	}
}