#include "stdafx.h"
#include "KFR3.h"

namespace LibSWBF2::Chunks::Mesh
{
	void KFR3::RefreshSize()
	{
		m_NumberOfBonesInThisAnimation.RefreshSize();
		m_CRCchecksum.RefreshSize();
		m_KeyFrameType.RefreshSize();
		m_NumberOfTranslationFrames.RefreshSize();
		m_NumberOfRotationFrames.RefreshSize();
		m_TranslationFrameIndex.RefreshSize();
		m_TranslationInXYZ.size() * Vector3::SIZE;
		m_RotationFrameIndex.RefreshSize();
		m_QuaternionRotationInXYZW.size() * Vector4::SIZE;

		m_Size =
			m_NumberOfBonesInThisAnimation.GetSize() +
			m_CRCchecksum.GetSize() +
			m_KeyFrameType.GetSize() +
			m_NumberOfTranslationFrames.GetSize() +
			m_NumberOfRotationFrames.GetSize() +
			m_TranslationFrameIndex.GetSize() +
			m_TranslationInXYZ.GetSize() +
			m_RotationFrameIndex.GetSize() +
			m_QuaternionRotationInXYZW.GetSize();
	}

	void KFR3::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_NumberOfBonesInThisAnimation.WriteToStream(stream);
		m_CRCchecksum.WriteToStream(stream);
		m_KeyFrameType.WriteToStream(stream);
		m_NumberOfTranslationFrames.WriteToStream(stream);
		m_NumberOfRotationFrames.WriteToStream(stream);
		m_TranslationFrameIndex.WriteToStream(stream);
		stream.WriteUInt32((uint32_t)m_TranslationInXYZ.size());
		
		for (uint32_t i = 0; i < m_TranslationInXYZ; ++i)
		{
			m_TranslationInXYZ[i].WriteToStream(stream);
		}
		
		m_RotationFrameIndex.WriteToStream(stream);
		stream.WriteUInt32((uint32_t)m_QuaternionRotationInXYZW.size());
		
		for (uint32_t i = 0; i < m_QuaternionRotationInXYZW; ++i)
		{
			m_QuaternionRotationInXYZW[i].WriteToStream(stream);
		}
	}

	void KFR3::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		m_NumberOfBonesInThisAnimation = stream.ReadUInt32();
		m_CRCchecksum = stream.ReadUInt32();
		m_KeyFrameType = stream.ReadUInt32();
		m_NumberOfTranslationFrames = stream.ReadUInt32();
		m_NumberOfRotationFrames = stream.ReadUInt32();
		m_TranslationFrameIndex = stream.ReadUInt32();
		m_TranslationInXYZ = stream.ReadUInt32();
		
		for (uint32_t i = 0; i < m_TranslationInXYZ; ++i)
		{
			Vector3& dataStream = m_TranslationInXYZ;
			dataStream.ReadFromStream(stream);
		}
		
		m_RotationFrameIndex = stream.ReadUInt32();
		m_QuaternionRotationInXYZW = stream.ReadUInt32();
		
		for (uint32_t i = 0; i < m_QuaternionRotationInXYZW; ++i)
		{
			Vector4& dataStream = m_QuaternionRotationInXYZW;
			dataStream.ReadFromStream(stream);
		}
		
		BaseChunk::EnsureEnd(stream);
	}
}