#pragma once
#include "Chunks\BaseChunk.h"
#include "CYCL.h"
#include "KFR3.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MSH;

	struct LIBSWBF2_EXP ANM2 : public BaseChunk
	{
		CYCL m_AnimationCycle;
		KFR3 m_KeyFrames;

	protected:
		friend MSH;

		ANM2() = default;
		~ANM2() = default;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}