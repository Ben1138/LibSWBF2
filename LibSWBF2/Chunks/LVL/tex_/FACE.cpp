#include "stdafx.h"
#include "FACE.h"

namespace LibSWBF2::Chunks::LVL
{
	void FACE::RefreshSize()
	{
		throw std::runtime_error("Not implemented!");
	}

	void FACE::WriteToStream(FileWriter& stream)
	{
		throw std::runtime_error("Not implemented!");
	}

	void FACE::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);

		while (PositionInChunk(stream.GetPosition()))
		{
			LVL_* lvl = new LVL_();
			READ_CHILD(stream, lvl);
			m_LVLs.Add(lvl);
		}

		BaseChunk::EnsureEnd(stream);
	}
}