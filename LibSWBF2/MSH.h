#pragma once
#include "BaseChunk.h"
#include "SHVO.h"
#include "MSH2.h"

namespace LibSWBF2::Chunks::MSH
{
	struct MSH : public BaseChunk
	{
		MSH();
		~MSH();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

	private:
		SHVO shvo;
		MSH2 msh2;
	};
}