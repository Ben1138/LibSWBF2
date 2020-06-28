#include "stdafx.h"
#include "tex_.h"
#include "Exceptions.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::texture
{
	void tex_::RefreshSize()
	{
		throw LibException("Not implemented!");
	}

	void tex_::WriteToStream(FileWriter& stream)
	{
		throw LibException("Not implemented!");
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
}