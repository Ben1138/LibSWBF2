#include "stdafx.h"
#include "LVL_.h"

namespace LibSWBF2::Chunks::LVL
{
	void LVL_::RefreshSize()
	{
		throw std::runtime_error("Not implemented!");
	}

	void LVL_::WriteToStream(FileWriter& stream)
	{
		throw std::runtime_error("Not implemented!");
	}

	void LVL_::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);

		ReadChildExplicit(stream, p_Info, HeaderNames::INFO);
		ReadChildExplicit(stream, p_Body, HeaderNames::BODY);

		BaseChunk::EnsureEnd(stream);
	}
}