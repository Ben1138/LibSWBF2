#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Types/List.h>

/*
This is a common chunk type, but for now its
usefulness as a base class is unclear...
*/
namespace LibSWBF2::Chunks::LVL::common
{
	struct LIBSWBF2_API SCOP : public GenericChunk<"SCOP"_m>{};
}
