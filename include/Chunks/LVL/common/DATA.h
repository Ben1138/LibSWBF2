#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/RawData.h"
#include "Types/Enums.h"

namespace LibSWBF2::Chunks::LVL::common
{
	struct LIBSWBF2_API DATA : public GenericChunk<"DATA"_m>
	{
		static uint32_t PeekDATATag(FileReader& stream);
	};
}
