#pragma once
#include "Chunks/GenericChunk.h"
#include "SMNA.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	struct LIBSWBF2_API BIN_ : public GenericChunk<"BIN_"_m>
	{
	public:
		SMNA* p_SMNA;	// info?

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}