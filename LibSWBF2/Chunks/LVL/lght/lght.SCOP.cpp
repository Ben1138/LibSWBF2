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
    THROW("Not implemented!");
}

void SCOP_LGHT::WriteToStream(FileWriter& stream)
{
    THROW("Not implemented!");
}

void SCOP_LGHT::ReadFromStream(FileReader& stream)
{ 
    /*
     After reading the header, just read the children,
     as a SCOP is just length int32 + DATA children.
     */
    
    BaseChunk::ReadFromStream(stream);
    Check(stream);

    while (ThereIsAnother(stream))
    {
        READ_CHILD(stream, p_RotationChunk);
        READ_CHILD(stream, p_PositionChunk);
        READ_CHILD(stream, p_TypeChunk);
        READ_CHILD(stream, p_ColorChunk);

        while (ThereIsAnother(stream))
        {
            READ_CHILD_GENERIC(stream); //temp till I figure out best way to handle
                                        //fields specific to light types
        }
    }
    BaseChunk::EnsureEnd(stream);
}
    
}
