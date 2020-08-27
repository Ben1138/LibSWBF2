#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
#include "Chunks/LVL/common/DATA.h"
#include "Chunks/LVL/common/SCOP.h"

#include "Chunks/LVL/lght/lght.SCOP.h"
#include "Chunks/LVL/lght/lighttag.DATA.h"
#include "Chunks/LVL/lght/lighttype.DATA.h"
#include "Chunks/LVL/lght/vec4.DATA.h"
#include "Chunks/LVL/lght/vec3.DATA.h"


/*
'lght' chunk spec

Example with a single omnidirectional light

'lght' (number of lights not explicitly stated, presumably derived from lght chunk length)

	'name' (? 4 bytes, seems to signal start of light list, kind of redundant...)
  
    lightinstance   {
 
    'data' local light/global light flag (? bytes), name string (? bytes)

    'scop' lighttype/chunklength (uint32) a8 = omni, f4 = spot, e0 = dir
                                          c0 = omni (cast specular)
        'data' rotation, 25 (28) bytes

        'data' position, 21 (24) bytes

        'data' 		  ?, 13 (16) bytes

        'data'    color, 21 (24) bytes

        'data'		  ?,  9 (12) bytes

        'data'		  ?, 13 (16) bytes
    }
 
    next lightinstance {
    ...
    ...
    ...
    }
*/

using namespace LibSWBF2::Chunks::LVL::common;

namespace LibSWBF2::Chunks::LVL::lght
{

struct LIBSWBF2_API lght : public GenericChunk<"lght"_m>
{
public:
	void RefreshSize() override;
	void WriteToStream(FileWriter& stream) override;
	void ReadFromStream(FileReader& stream) override;
    bool m_Empty = false;

    List<DATA_TAG *> p_LightTags;
    List<SCOP_LGHT *> p_LightBodies;
    int m_NumLights = 0;

private:
    inline static bool skip = false;
};

}
