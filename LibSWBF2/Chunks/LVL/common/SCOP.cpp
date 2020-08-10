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

void SCOP::ReadFromStream(FileReader& stream)
{
    BaseChunk::ReadFromStream(stream);
    Check(stream);
    
    /*
     After reading the header, just read the children,
     as a SCOP is just length int32 + DATA children.
     */
    
    DATA *newChild;
    do {
        /*
         Maybe I should just use the inherited method?
         Unsure about GenericChunkNC cast...
         */
        
        try {
            READ_CHILD(stream, newChild);
        } catch (LibException& e)
        {
            delete newChild;
            newChild = nullptr;

            LOG_ERROR(e.what());
            //LOG_ERROR("Skipping invalid Chunk: '{}' at pos: {}", nextHead, stream.GetPosition() - 8);
            break;
        }
    } while (true);
    
    BaseChunk::EnsureEnd(stream);

    
}
    
}
    
