#include "stdafx.h"
#include "zaa_.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	void zaa_::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void zaa_::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void zaa_::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);
		
		//BaseChunk::EnsureEnd(stream);
		//return;



		READ_CHILD(stream, p_Name);

		// TODO: handle SMNA chunks correctly, before continue reading!
		// Apparently, their chunk size is always 0 ?

		READ_CHILD(stream, p_Bin);

		/*
		while (ThereIsAnother(stream))
		{
			READ_CHILD_GENERIC(stream);
		}
		*/

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