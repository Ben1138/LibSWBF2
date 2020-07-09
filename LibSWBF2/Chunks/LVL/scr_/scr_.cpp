#include "stdafx.h"
#include "scr_.h"
#include "Exceptions.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::script
{
	void scr_::RefreshSize()
	{
		throw LibException("Not implemented!");
	}

	void scr_::WriteToStream(FileWriter& stream)
	{
		throw LibException("Not implemented!");
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

	String scr_::ToString()
	{
		return fmt::format(
			"Name: {}\n\n"
			"Info: {}\n",
			p_Name->m_Text,
			p_Info->ToString()
		).c_str();
	}
}