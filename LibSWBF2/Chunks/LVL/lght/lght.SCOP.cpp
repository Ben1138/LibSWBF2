#include "stdafx.h"
#include "Logging/Logger.h"
#include "DirectX/DXHelpers.h"
#include "InternalHelpers.h"
#include "FileReader.h"

#include "lght.SCOP.h"
#include "Chunks/LVL/lght/vec3.DATA.h"
#include "Chunks/LVL/lght/vec4.DATA.h"
#include "Chunks/LVL/lght/lighttype.DATA.h"

#include <algorithm>
#include <cstring>


using namespace LibSWBF2::Chunks::LVL::common;


namespace LibSWBF2::Chunks::LVL::lght
{
    
void SCOP_LGHT::RefreshSize()
{
    //THROW("Not implemented!");
    return;
}

void SCOP_LGHT::WriteToStream(FileWriter& stream)
{
    THROW("Not implemented!");
}

String SCOP_LGHT::ToString()
{
    return String("SCOP");
}

void SCOP_LGHT::ReadFromStream(FileReader& stream)
{ 
    /*
     After reading the header, just read the children,
     as a SCOP is just length int32 + DATA children.
     */
    
    BaseChunk::ReadFromStream(stream);
    Check(stream);

    DATA_VEC4 *rotation;
    DATA_VEC3 *position;
    DATA_LIGHTTYPE *type;
    DATA_VEC3 *color;

    DATA *throwaway;

    while (ThereIsAnother(stream))
    {
        READ_CHILD(stream, rotation);
        READ_CHILD(stream, position);
        READ_CHILD(stream, type);
        READ_CHILD(stream, color);

        p_DataFields.Add(rotation);
        p_DataFields.Add(position);
        p_DataFields.Add(type);
        p_DataFields.Add(color);

        while (ThereIsAnother(stream))
        {
            READ_CHILD(stream,throwaway);
        }
    }
    BaseChunk::EnsureEnd(stream);
}
    
}
