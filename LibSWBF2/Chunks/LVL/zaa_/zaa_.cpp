#include "stdafx.h"
#include "zaa_.h"
#include "Exceptions.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	void zaa_::RefreshSize()
	{
		throw LibException("Not implemented!");
	}

	void zaa_::WriteToStream(FileWriter& stream)
	{
		throw LibException("Not implemented!");
	}

	void zaa_::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		READ_CHILD(stream, p_Name);
		READ_CHILD(stream, p_Bin);

		while (ThereIsAnother(stream))
		{
			READ_CHILD_GENERIC(stream);
		}

		BaseChunk::EnsureEnd(stream);
	}

	String zaa_::ToString()
	{
		return fmt::format(
			"Name: {}\n\n",
			p_Name->m_Text
		).c_str();
	}
}