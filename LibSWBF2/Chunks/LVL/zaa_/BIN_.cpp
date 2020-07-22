#include "stdafx.h"
#include "BIN_.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	void BIN_::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void BIN_::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void BIN_::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		READ_CHILD(stream, p_SMNA);

		while (ThereIsAnother(stream))
		{
			READ_CHILD_GENERIC(stream);
		}

		BaseChunk::EnsureEnd(stream);
	}
}