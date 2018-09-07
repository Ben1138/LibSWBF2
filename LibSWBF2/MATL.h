#pragma once
#include "BaseChunk.h"
#include "NAME.h"
#include "MATD.h"

namespace LibSWBF2::Chunks::MSH
{
	struct MATL : public BaseChunk
	{
		MATL();
		~MATL();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

	private:
		vector<MATD> Materials;
	};
}