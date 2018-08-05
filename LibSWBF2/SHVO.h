#pragma once
#include "BaseChunk.h"

namespace LibSWBF2
{
	struct SHVO : public BaseChunk
	{
		SHVO();
		~SHVO();

		void WriteToStream(ofstream& stream) override;
		void ReadFromStream(ifstream& stream) override;

	private:
		int ShadowVolume;
	};
}