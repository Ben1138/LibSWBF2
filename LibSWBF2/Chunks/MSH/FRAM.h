#pragma once
#include "Chunks/BaseChunk.h"

namespace LibSWBF2::Chunks::MSH
{
	struct SINF;

	struct LIBSWBF2_API FRAM : public BaseChunk
	{
		FRAM() = default;
		~FRAM() = default;

		int32_t m_FrameRangeStart = 0;
		int32_t m_FrameRangeEnd = 0;
		float_t m_FramesPerSecond = 0.0f;

	protected:
		friend SINF;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}