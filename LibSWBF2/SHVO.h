#pragma once
#include "stdafx.h"
#include "BaseChunk.h"

namespace LibSWBF2
{
	struct SHVO : public BaseChunk
	{
	private:
		int ShadowVolume;

	public:
		SHVO();
		~SHVO();

		void WriteToStream(ofstream& stream) override;
		void ReadFromStream(ifstream& stream) override;

	};
}