#pragma once

#include "stdafx.h"
#include "Chunks/GenericChunk.h"
#include "Chunks/RawData.h"
#include "Types/Enums.h"


namespace LibSWBF2::Chunks::LVL::common
{

struct LIBSWBF2_API DATA : public RawData<"DATA"_m> {};

}
