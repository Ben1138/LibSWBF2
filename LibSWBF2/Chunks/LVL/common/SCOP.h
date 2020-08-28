#pragma once

/*
This is a common chunk type, but for now its
usefulness as a base class is unclear...
*/

#include "stdafx.h"


#include "Chunks/GenericChunk.h"
#include "DATA.h"
#include "Types/List.h"

namespace LibSWBF2::Chunks::LVL::common
{
struct LIBSWBF2_API SCOP : public GenericChunk<"SCOP"_m>{};
}