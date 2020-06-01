#include "stdafx.h"
#include "tex_.h"

namespace LibSWBF2::Chunks::LVL
{
	void tex_::RefreshSize()
	{
		throw std::runtime_error("Not implemented!");
	}

	void tex_::WriteToStream(FileWriter& stream)
	{
		throw std::runtime_error("Not implemented!");
	}

	void tex_::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);

		READ_CHILD(stream, p_Name);
		READ_CHILD(stream, p_Info);

		while (PositionInChunk(stream.GetPosition()))
		{
			FMT_* fmt;
			READ_CHILD(stream, fmt);
			m_FMTs.Add(fmt);
		}

		BaseChunk::EnsureEnd(stream);
	}
}