#include "stdafx.h"
#include "CYCL.h"

namespace LibSWBF2::Chunks::Mesh
{
	void CYCL::RefreshSize()
	{
		m_Size = (uint32_t)(sizeof(uint32_t) + (Animation::SIZE * m_Animations.Size()));
	}

	void CYCL::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteUInt32((uint32_t)m_Animations.Size());

		for (size_t i = 0; i < m_Animations.Size(); ++i)
		{
			m_Animations[i].WriteToStream(stream);
		}
	}

	void CYCL::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		uint32_t numOfAnims = stream.ReadUInt32();
		
		m_Animations.Clear();
		m_Animations.Resize(numOfAnims);

		for (size_t i = 0; i < numOfAnims; ++i)
		{
			Animation& anim = m_Animations.Emplace();
			anim.ReadFromStream(stream);
		}

		BaseChunk::EnsureEnd(stream);
	}
}