#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MNDX : public BaseChunk
	{
		MNDX();
		~MNDX();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

	private:
		uint32_t m_ModelIndex;
	};
}
