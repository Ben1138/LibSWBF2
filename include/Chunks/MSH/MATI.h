#pragma once
#include "Chunks/BaseChunk.h"

namespace LibSWBF2::Chunks::MSH
{
	struct SEGM;

	struct LIBSWBF2_API MATI : public BaseChunk
	{
		MATI() = default;
		~MATI() = default;

		uint32_t m_MaterialIndex = 0;

	protected:
		friend SEGM;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}