#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::MSH
{
	struct SHVO : public BaseChunk
	{
		SHVO();
		~SHVO();

		void RefreshSize() override;
		void WriteToStream(ofstream& stream) override;
		void ReadFromStream(ifstream& stream) override;

	private:
		int32_t ShadowVolume;
	};
}