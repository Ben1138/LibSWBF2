#pragma once
#include "BaseChunk.h"
#include "NAME.h"
#include "MATD_DATA.h"

namespace LibSWBF2::Chunks::MSH
{
	struct MATD : public BaseChunk
	{
		MATD();
		~MATD();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

	private:
		NAME name;
		MATD_DATA data;
		NAME tx0d;
		NAME tx1d;
		NAME tx2d;
		NAME tx3d;
	};
}