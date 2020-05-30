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

		ReadChildExplicit(stream, p_Name, HeaderNames::NAME);
		ReadChildExplicit(stream, p_Info, HeaderNames::INFO);

		while (PositionInChunk(stream.GetPosition()))
		{
			FMT_* fmt = new FMT_();
			ReadChildExplicit(stream, fmt, HeaderNames::FMT_);
			m_FMTs.Add(fmt);
		}

		BaseChunk::EnsureEnd(stream);
	}
}