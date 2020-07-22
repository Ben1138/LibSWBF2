#include "stdafx.h"
#include "FACE.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::texture
{
	void FACE::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void FACE::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void FACE::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		while (ThereIsAnother(stream))
		{
			LVL_* lvl = new LVL_();
			READ_CHILD(stream, lvl);
			m_LVLs.Add(lvl);
		}

		BaseChunk::EnsureEnd(stream);
	}
}