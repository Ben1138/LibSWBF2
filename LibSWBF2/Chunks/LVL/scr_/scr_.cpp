#include "stdafx.h"
#include "scr_.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::script
{
	void scr_::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void scr_::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void scr_::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		READ_CHILD(stream, p_Name);
		READ_CHILD(stream, p_Info);
		READ_CHILD(stream, p_Body);

		BaseChunk::EnsureEnd(stream);
	}

	String scr_::ToString() const
	{
		return fmt::format(
			"Name: {}\n\n"
			"Info: {}\n",
			p_Name->m_Text,
			p_Info->ToString()
		).c_str();
	}
}