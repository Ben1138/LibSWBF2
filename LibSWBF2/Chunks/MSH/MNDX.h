#pragma once
#include "Chunks\BaseChunk.h"

namespace LibSWBF2::Chunks::MSH
{
	struct MODL;

	struct LIBSWBF2_API MNDX : public BaseChunk
	{
		MNDX() = default;
		~MNDX() = default;

		uint32_t m_ModelIndex = 0;

	protected:
		friend MODL;
		
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}
