#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MODL;

	struct MNDX : public BaseChunk
	{
		MNDX() = default;
		~MNDX() = default;

		uint32_t m_ModelIndex;

	protected:
		friend MODL;
		
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}
