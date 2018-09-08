#pragma once
#include "BaseChunk.h"
#include "NAME.h"
#include "MTYP.h"

namespace LibSWBF2::Chunks::MSH
{
	struct FLGS : public BaseChunk
	{
		FLGS();
		~FLGS();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

	private:
		uint32_t ModelDisplayFlags;	// unknown?
	};
}
