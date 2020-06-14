#pragma once
#include "Chunks\BaseChunk.h"

namespace LibSWBF2::Chunks::MSH
{
	struct MODL;

	struct LIBSWBF2_API FLGS : public BaseChunk
	{
		FLGS() = default;
		~FLGS() = default;

		uint32_t m_ModelDisplayFlags = 0;	// unknown?

	protected:
		friend MODL;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}
