#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct SHVO : public BaseChunk
	{
		SHVO();
		~SHVO();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

	private:
		int32_t ShadowVolume;
	};
}