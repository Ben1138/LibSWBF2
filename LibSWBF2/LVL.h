#pragma once
#include "GenericChunk.h"

namespace LibSWBF2::Chunks::LVL
{
	struct LIBSWBF2_EXP LVL : public GenericChunk
	{
	public:
		static LVL* Create();
		static void Destroy(LVL* lvl);		

	protected:
		LVL() = default;
		~LVL() = default;

		void ReadFromStream(FileReader& stream) override;
	};
}