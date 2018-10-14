#include "stdafx.h"
#include "BoneFrames.h"

namespace LibSWBF2::Types
{
	uint32_t BoneFrames::GetSize()
	{
		return (uint32_t)((sizeof(uint32_t) * 2) + (TranslationFrame::SIZE * m_TranslationFrames.size()) + (RotationFrame::SIZE * m_RotationFrames.size()));
	}

	void BoneFrames::WriteToStream(FileWriter& stream)
	{
		stream.WriteUInt32(m_CRCchecksum);
		stream.WriteUInt32(m_KeyFrameType);

		stream.WriteUInt32((uint32_t)m_TranslationFrames.size());
		stream.WriteUInt32((uint32_t)m_RotationFrames.size());

		for (size_t i = 0; i < m_TranslationFrames.size(); ++i)
		{
			m_TranslationFrames[i].WriteToStream(stream);
		}

		for (size_t i = 0; i < m_RotationFrames.size(); ++i)
		{
			m_RotationFrames[i].WriteToStream(stream);
		}
	}

	void BoneFrames::ReadFromStream(FileReader& stream)
	{
		m_CRCchecksum = stream.ReadUInt32();
		m_KeyFrameType = stream.ReadUInt32();

		const uint32_t numTranFrames = stream.ReadUInt32();
		const uint32_t numRotFrames = stream.ReadUInt32();

		m_TranslationFrames.clear();
		m_TranslationFrames.reserve(numTranFrames);
		m_RotationFrames.clear();
		m_RotationFrames.reserve(numRotFrames);

		for (size_t i = 0; i < numTranFrames; ++i)
		{
			TranslationFrame& tran = m_TranslationFrames.emplace_back();
			tran.ReadFromStream(stream);
		}

		for (size_t i = 0; i < numRotFrames; ++i)
		{
			RotationFrame& rot = m_RotationFrames.emplace_back();
			rot.ReadFromStream(stream);
		}
	}
}