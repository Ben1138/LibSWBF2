#pragma once
#include <LibSWBF2/Chunks/BaseChunk.h>
#include <LibSWBF2/Chunks/MSH/CYCL.h>
#include <LibSWBF2/Chunks/MSH/KFR3.h>

namespace LibSWBF2::Chunks::MSH
{
	struct MSH;

	struct LIBSWBF2_API ANM2 : public BaseChunk
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