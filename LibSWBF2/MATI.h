#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct SEGM;

	struct LIBSWBF2_EXP MATI : public BaseChunk
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