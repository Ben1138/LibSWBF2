#include "stdafx.h"
#include "MSH2.h"

namespace LibSWBF2::Chunks::Mesh
{
	MSH2::MSH2()
	{

	}

	MSH2::~MSH2()
	{

	}

	void MSH2::RefreshSize()
	{
		m_SINF.RefreshSize();
		m_MATL.RefreshSize();

		m_Size = m_SINF.GetSize() + m_MATL.GetSize();
	}

	void MSH2::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_SINF.WriteToStream(stream);
		m_MATL.WriteToStream(stream);
	}

	void MSH2::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);

		while (PositionInChunk(stream.GetPosition()))
		{
			ChunkHeader head = stream.ReadChunkHeader(true);

			if (head == HeaderNames::SINF)
			{
				m_SINF.ReadFromStream(stream);
			}
			else if (head == HeaderNames::MATL)
			{
				m_MATL.ReadFromStream(stream);
			}
			else
			{
				SkipChunk(stream);
			}
		}
	}
}