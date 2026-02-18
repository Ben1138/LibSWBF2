#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Chunks/RawData.h>
#include <LibSWBF2/Types/Enums.h>

namespace LibSWBF2::Chunks::LVL::common
{
	struct LIBSWBF2_API DATA : public GenericChunk<"DATA"_m>
	{
		static uint32_t PeekDATATag(FileReader& stream);
	};
}
