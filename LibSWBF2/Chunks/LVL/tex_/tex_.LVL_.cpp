#include "stdafx.h"
#include "tex_.LVL_.h"
#include "Exceptions.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::LVL_texture
{
	void LVL_::RefreshSize()
	{
		throw LibException("Not implemented!");
	}

	void LVL_::WriteToStream(FileWriter& stream)
	{
		throw LibException("Not implemented!");
	}

	void LVL_::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		READ_CHILD(stream, p_Info);
		READ_CHILD(stream, p_Body);

		BaseChunk::EnsureEnd(stream);
	}
}