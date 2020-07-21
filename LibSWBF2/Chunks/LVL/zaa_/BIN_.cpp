#include "stdafx.h"
#include "BIN_.h"
#include "Exceptions.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	void BIN_::RefreshSize()
	{
		throw LibException("Not implemented!");
	}

	void BIN_::WriteToStream(FileWriter& stream)
	{
		throw LibException("Not implemented!");
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