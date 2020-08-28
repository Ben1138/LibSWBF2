#pragma once

#include "stdafx.h"
#include "Chunks/GenericChunk.h"
#include "Chunks/LVL/common/DATA.h"
#include "Chunks/LVL/lght/vec3.DATA.h"
#include "Chunks/LVL/lght/vec4.DATA.h"
#include "Chunks/LVL/lght/lighttype.DATA.h"
#include "Types/List.h"

using LibSWBF2::Chunks::LVL::common::DATA;

namespace LibSWBF2::Chunks::LVL::lght
{

struct LIBSWBF2_API SCOP_LGHT : public GenericChunk<"SCOP"_m>{
	
	void RefreshSize() override;
	void WriteToStream(FileWriter& stream) override;
	void ReadFromStream(FileReader& stream) override;

	DATA_VEC4 *p_RotationChunk;
    DATA_VEC3 *p_PositionChunk;
    DATA_LIGHTTYPE *p_TypeChunk;
    DATA_VEC3 *p_ColorChunk;
};

}