#include "stdafx.h"
#include "ANM2.h"

namespace LibSWBF2::Chunks::Mesh
{
	void ANM2::RefreshSize()
	{
		m_AnimationCycle.RefreshSize();
		m_KeyFrames.RefreshSize();

		m_Size = m_AnimationCycle.GetSize() + m_KeyFrames.GetSize();
	}

	void ANM2::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_AnimationCycle.WriteToStream(stream);
		m_KeyFrames.WriteToStream(stream);
	}

	void ANM2::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);

		while (PositionInChunk(stream.GetPosition()))
		{
			ChunkHeader head = stream.ReadChunkHeader(true);

			if (head == HeaderNames::CYCLE)
			{
				m_AnimationCycle.ReadFromStream(stream);
			}
			else if (head == HeaderNames::KFR3)
			{
				m_KeyFrames.ReadFromStream(stream);
			}
			else
			{
				UnexpectedChunk(stream);
			}
		}

		BaseChunk::EnsureEnd(stream);
	}
}