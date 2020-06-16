#include "stdafx.h"
#include "FACE.h"
#include "Exceptions.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::texture
{
	void FACE::RefreshSize()
	{
		throw LibException("Not implemented!");
	}

	void FACE::WriteToStream(FileWriter& stream)
	{
		throw LibException("Not implemented!");
	}

	void FACE::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		while (PositionInChunk(stream.GetPosition()))
		{
			LVL_* lvl = new LVL_();
			READ_CHILD(stream, lvl);
			m_LVLs.Add(lvl);
		}

		BaseChunk::EnsureEnd(stream);
	}
}