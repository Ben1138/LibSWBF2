#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct FLGS : public BaseChunk
	{
		FLGS();
		~FLGS();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		uint32_t m_ModelDisplayFlags;	// unknown?
	};
}
