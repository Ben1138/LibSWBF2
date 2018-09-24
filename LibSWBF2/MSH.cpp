#include "stdafx.h"
#include "MSH.h"

namespace LibSWBF2::Chunks::Mesh
{
	MSH::MSH()
	{

	}

	MSH::~MSH()
	{

	}

	void MSH::RefreshSize()
	{
		m_SHVO.RefreshSize();

		m_Size = m_SHVO.GetSize();
	}

	void MSH::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_SHVO.WriteToStream(stream);
	}

	void MSH::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);

		while (PositionInChunk(stream.GetPosition()))
		{
			ChunkHeader head = stream.ReadChunkHeader(true);

			// sadly, switch-case is not possible here (Error C2051)
			if (head == HeaderNames::SHVO)
			{
				m_SHVO.ReadFromStream(stream);
			}
			else if (head == HeaderNames::MSH2)
			{
				m_MSH2.ReadFromStream(stream);
			}
			else
			{
				SkipChunk(stream);
			}
		}
	}
}