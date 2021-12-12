#include "pch.h"
#include "BoneFrames.h"
#include "FileWriter.h"
#include "FileReader.h"

namespace LibSWBF2::Types
{
	uint32_t BoneFrames::GetDataSize()
	{
		return (uint32_t)((sizeof(uint32_t) * 2) + (TranslationFrame::SIZE * m_TranslationFrames.Size()) + (RotationFrame::SIZE * m_RotationFrames.Size()));
	}

	void BoneFrames::WriteToStream(FileWriter& stream)
	{
		stream.WriteUInt32(m_CRCchecksum);
		stream.WriteUInt32(m_KeyFrameType);

		stream.WriteUInt32((uint32_t)m_TranslationFrames.Size());
		stream.WriteUInt32((uint32_t)m_RotationFrames.Size());

		for (size_t i = 0; i < m_TranslationFrames.Size(); ++i)
		{
			m_TranslationFrames[i].WriteToStream(stream);
		}

		for (size_t i = 0; i < m_RotationFrames.Size(); ++i)
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

		m_TranslationFrames.Clear();
		m_TranslationFrames.Resize(numTranFrames);
		m_RotationFrames.Clear();
		m_RotationFrames.Resize(numRotFrames);

		for (size_t i = 0; i < numTranFrames; ++i)
		{
			TranslationFrame& tran = m_TranslationFrames.Emplace();
			tran.ReadFromStream(stream);
		}

		for (size_t i = 0; i < numRotFrames; ++i)
		{
			RotationFrame& rot = m_RotationFrames.Emplace();
			rot.ReadFromStream(stream);
		}
	}
}