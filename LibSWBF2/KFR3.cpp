#include "stdafx.h"
#include "KFR3.h"

namespace LibSWBF2::Chunks::Mesh
{
	void KFR3::RefreshSize()
	{
		m_Size = 0;

		for (size_t i = 0; i < m_BoneFrames.size(); ++i)
		{
			m_Size += m_BoneFrames[i].GetSize();
		}
	}

	void KFR3::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteUInt32((uint32_t)m_BoneFrames.size());

		for (size_t i = 0; i < m_BoneFrames.size(); ++i)
		{
			m_BoneFrames[i].WriteToStream(stream);
		}
	}

	void KFR3::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		uint32_t num = stream.ReadUInt32();

		m_BoneFrames.clear();
		m_BoneFrames.reserve(num);

		for (uint32_t i = 0; i < num; ++i)
		{
			BoneFrames& bf = m_BoneFrames.emplace_back();
			bf.ReadFromStream(stream);
		}

		BaseChunk::EnsureEnd(stream);
	}
}