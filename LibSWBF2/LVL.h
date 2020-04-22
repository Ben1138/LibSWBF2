#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::LVL
{
	struct LIBSWBF2_EXP LVL : public BaseChunk
	{
		static LVL* Create();
		static void Destroy(LVL* lvl);

		

	protected:
		LVL() = default;
		~LVL() = default;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}