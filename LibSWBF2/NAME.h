#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::MSH
{
	struct NAME : public BaseChunk
	{
		NAME();
		~NAME();

		void RefreshSize() override;
		void WriteToStream(ofstream& stream) override;
		void ReadFromStream(ifstream& stream) override;

	private:
		string Text;
	};
}