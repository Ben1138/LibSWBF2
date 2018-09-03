#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::MSH
{
	struct MSH2 : public BaseChunk
	{
		MSH2();
		~MSH2();

		void WriteToStream(ofstream& stream) override;
		void ReadFromStream(ifstream& stream) override;

	private:
		int32_t ShadowVolume;
	};
}