#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
#include "Chunks/LVL/common/DATA.h"
#include "Chunks/LVL/common/SCOP.h"
#include "Chunks/LVL/lght/lght.SCOP.h"
#include "Chunks/LVL/lght/string.DATA.h"
#include "Chunks/LVL/lght/vec4.DATA.h"
#include "Chunks/LVL/lght/vec3.DATA.h"


using namespace LibSWBF2::Chunks::LVL::common;

namespace LibSWBF2::Chunks::LVL::lght
{
    struct LIBSWBF2_API lght : public GenericChunk<"lght"_m>
    {
    public:
	    void RefreshSize() override;
	    void WriteToStream(FileWriter& stream) override;
	    void ReadFromStream(FileReader& stream) override;

        List<DATA_STRING *> p_LightTags;
        List<SCOP_LGHT *> p_LightBodies;

        DATA_STRING *p_GlobalLightingTag = 0;
        SCOP_LGHT *p_GlobalLightingBody = 0;

        STR<"NAME"_m> *p_Marker; //unknown purpose, hashed layer name?
    };
}