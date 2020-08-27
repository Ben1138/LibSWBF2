#include "stdafx.h"
#include "Logging/Logger.h"
#include "DirectX/DXHelpers.h"
#include "InternalHelpers.h"
#include "FileReader.h"

#include "SCOP.h"

#include <algorithm>
#include <cstring>

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

        p_dataFields.Add(rotation);
        p_dataFields.Add(position);
        p_dataFields.Add(type);
        p_dataFields.Add(color);

        while (ThereIsAnother(stream))
        {
            READ_CHILD(stream,throwaway);
        }
    }
    BaseChunk::EnsureEnd(stream);
}
    
}
