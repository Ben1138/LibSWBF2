#include "stdafx.h"
#include "ANM2.h"
#include "Chunks\HeaderNames.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::MSH
{
	void ANM2::RefreshSize()
	{
		m_AnimationCycle.RefreshSize();
		m_KeyFrames.RefreshSize();

		m_Size = m_AnimationCycle.GetDataSize() + m_KeyFrames.GetDataSize();
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

			if (head == "CYCL"_h)
			{
				m_AnimationCycle.ReadFromStream(stream);
			}
			else if (head == "KFR3"_h)
			{
				m_KeyFrames.ReadFromStream(stream);
			}
			else
			{
				SkipChunk(stream);
			}
		}

		BaseChunk::EnsureEnd(stream);
	}
}