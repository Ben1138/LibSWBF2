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

		READ_CHILD(stream, p_Info);
		READ_CHILD(stream, p_Body);

		BaseChunk::EnsureEnd(stream);
	}
}