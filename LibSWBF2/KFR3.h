#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct ANM2;

	struct KFR3 : public BaseChunk
	{
		KFR3() = default;
		~KFR3() = default;

		uint32_t m_NumberOfBonesInThisAnimation;
		uint32_t m_CRCchecksum;
		uint32_t m_KeyFrameType;
		uint32_t m_NumberOfTranslationFrames;
		uint32_t m_NumberOfRotationFrames;
		uint32_t m_TranslationFrameIndex;
		vector<Vector3> m_TranslationInXYZ;
		uint32_t m_RotationFrameIndex;
		vector<Vector4> m_QuaternionRotationInXYZW;

	protected:
		friend KFR3;
		
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}