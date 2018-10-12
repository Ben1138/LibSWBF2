#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct SINF;

	struct FRAM : public BaseChunk
	{
		FRAM() = default;
		~FRAM() = default;

		int32_t m_FrameRangeStart;
		int32_t m_FrameRangeEnd;
		float_t m_FramesPerSecond;

	protected:
		friend SINF;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}