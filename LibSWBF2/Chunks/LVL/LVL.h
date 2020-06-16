#pragma once
#include "Chunks/GenericChunk.h"

namespace LibSWBF2::Chunks::LVL
{
	struct LIBSWBF2_API LVL : public GenericChunk<"ucfb"_m>
	{
	public:
		static LVL* Create()
		{
			return new LVL();
		}

		static void Destroy(LVL* lvl)
		{
			delete lvl;
		}

	protected:
		LVL() = default;
		~LVL() = default;
	};
}