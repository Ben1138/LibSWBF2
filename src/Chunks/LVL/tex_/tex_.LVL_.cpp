#include <LibSWBF2/pch.h>
#include <LibSWBF2/Chunks/LVL/tex_/tex_.LVL_.h>
#include "InternalHelpers.h"
#include <LibSWBF2/IO/FileReader.h>

namespace LibSWBF2::Chunks::LVL::LVL_texture
{
	void LVL_::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void LVL_::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
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