#include "stdafx.h"
#include "FMT_.h"

namespace LibSWBF2::Chunks::LVL::texture
{
	void FMT_::RefreshSize()
	{
		throw std::runtime_error("Not implemented!");
	}

	void FMT_::WriteToStream(FileWriter& stream)
	{
		throw std::runtime_error("Not implemented!");
	}

	void FMT_::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		READ_CHILD(stream, p_Info);
		READ_CHILD(stream, p_Face);

		BaseChunk::EnsureEnd(stream);
	}
}