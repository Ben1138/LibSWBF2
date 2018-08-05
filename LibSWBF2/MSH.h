#pragma once
#include "stdafx.h"
#include "BaseChunk.h"
#include "SHVO.h"

namespace LibSWBF2
{
	struct MSH : public BaseChunk
	{
		MSH();
		~MSH();

		void WriteToStream(ofstream& stream) override;
		void ReadFromStream(ifstream& stream) override;

	private:
		SHVO shvo;
	};
}