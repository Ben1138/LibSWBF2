#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MODL;

	struct FLGS : public BaseChunk
	{
		FLGS();
		~FLGS();

		uint32_t m_ModelDisplayFlags;	// unknown?

	protected:
		friend MODL;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}
