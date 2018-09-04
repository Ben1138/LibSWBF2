#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::MSH
{
	struct NAME : public BaseChunk
	{
		NAME();
		~NAME();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

	private:
		string Text;
	};
}