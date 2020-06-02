#pragma once
#include "Chunks\BaseChunk.h"

namespace LibSWBF2::Chunks::MSH
{
	struct MSH;

	struct LIBSWBF2_EXP SHVO : public BaseChunk
	{
		SHVO() = default;
		~SHVO() = default;

		int32_t m_ShadowVolume = 0;

	protected:
		friend MSH;
		
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}