#pragma once

#include "stdafx.h"
#include "Chunks/GenericChunk.h"
#include "Chunks/LVL/common/DATA.h"
#include "Chunks/LVL/lght/vec2.DATA.h"
#include "Chunks/LVL/lght/vec3.DATA.h"
#include "Chunks/LVL/lght/vec4.DATA.h"
#include "Chunks/LVL/lght/float.DATA.h"

#include "Types/List.h"


/*

Known field tags for DATA children in lght SCOP chunks, as they correspond to lgt/LGT files.
The first 4 aren't listed here since they are universal and required...

Local light SCOPs (in order of appearance):



CastShadow() - 0xee0ae9e7
Static() - 0x3bc290d2 
Range(float range) - 0xd20cdcfa
Cone(float innerAngle, float outerAngle) - 0x6a4b40dd (Spot specific)


Global light SCOP:

Light1(string name) - 0x3a6956db
Light2(string name) - 0xa76756da
top(3 ints) - 0x3cdc10a7
bottom(3 ints) - 0x2a6ba74e

*/


using LibSWBF2::Chunks::LVL::common::DATA;

namespace LibSWBF2::Chunks::LVL::lght
{

struct LIBSWBF2_API SCOP_LGHT : public GenericChunk<"SCOP"_m>{
	
	void RefreshSize() override;
	void WriteToStream(FileWriter& stream) override;
	void ReadFromStream(FileReader& stream) override;

	/*
	Local light fields
	*/

	DATA_VEC4 *p_RotationChunk;
    DATA_VEC3 *p_PositionChunk;
    DATA_FLOAT *p_TypeChunk;
    DATA_VEC3 *p_ColorChunk;

    DATA_FLOAT *p_RangeChunk;
    DATA_VEC2 *p_ConeChunk;

    /*
    Global light section fields
    */

    //DATA_LIGHT
    // *p_TopColorChunk;
    // *p_BottomColorChunk;










};

}