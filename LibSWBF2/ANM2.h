#pragma once
#include "BaseChunk.h"
#include "CYCL.h"
#include "KFR3.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct HEDR;

	struct ANM2 : public BaseChunk
	{
		CYCL m_AnimationCycle;
		KFR3 m_KeyFrames;

	protected:
		friend ANM2;

		ANM2() = default;
		~ANM2() = default;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}