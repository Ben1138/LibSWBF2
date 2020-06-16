#include "stdafx.h"
#include "KFR3.h"
#include "FileReader.h"
#include "FileWriter.h"

namespace LibSWBF2::Chunks::MSH
{
	void KFR3::RefreshSize()
	{
		m_Size = 0;

		for (size_t i = 0; i < m_BoneFrames.Size(); ++i)
		{
			m_Size += m_BoneFrames[i].GetDataSize();
		}
	}

	void KFR3::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteUInt32((uint32_t)m_BoneFrames.Size());

		for (size_t i = 0; i < m_BoneFrames.Size(); ++i)
		{
			m_BoneFrames[i].WriteToStream(stream);
		}
	}

	void KFR3::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		uint32_t num = stream.ReadUInt32();

		m_BoneFrames.Clear();
		m_BoneFrames.Resize(num);

		for (uint32_t i = 0; i < num; ++i)
		{
			BoneFrames& bf = m_BoneFrames.Emplace();
			bf.ReadFromStream(stream);
		}

		BaseChunk::EnsureEnd(stream);
	}
}