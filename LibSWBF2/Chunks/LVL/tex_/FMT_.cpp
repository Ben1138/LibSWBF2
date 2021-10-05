#include "pch.h"
#include "FMT_.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::texture
{
	void FMT_::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void FMT_::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
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