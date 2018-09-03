#pragma once
#include "BaseChunk.h"
#include "SHVO.h"

namespace LibSWBF2::Chunks::MSH
{
	struct MSH : public BaseChunk
	{
		MSH();
		~MSH();

		void RefreshSize() override;
		void WriteToStream(ofstream& stream) override;
		void ReadFromStream(ifstream& stream) override;

	private:
		SHVO shvo;
	};
}