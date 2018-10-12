#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct CAMR : public BaseChunk
	{				
		uint32_t m_Length;

	protected:
		CAMR() = default;
		~CAMR() = default;

		/*void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;*/
	};
}