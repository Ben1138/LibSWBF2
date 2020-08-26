#include "stdafx.h"
#include "Logging/Logger.h"
#include "DirectX/DXHelpers.h"
#include "InternalHelpers.h"
#include "FileReader.h"

#include "SCOP.h"

#include <algorithm>
#include <cstring>

namespace LibSWBF2::Chunks::LVL::common
{
    
void SCOP::RefreshSize()
{
    //THROW("Not implemented!");
    return;
}

void SCOP::WriteToStream(FileWriter& stream)
{
    THROW("Not implemented!");
}

String SCOP::ToString()
{
    return String("SCOP");
}

void SCOP::ReadFromStream(FileReader& stream)
{ 
    /*
     After reading the header, just read the children,
     as a SCOP is just length int32 + DATA children.
     */
    
    BaseChunk::ReadFromStream(stream);
    Check(stream);

    while (ThereIsAnother(stream))
    {
        DATA *tempField;        
        READ_CHILD(stream, tempField);

        p_dataFields.Add(tempField);
    }

    BaseChunk::EnsureEnd(stream);
}
    
}
