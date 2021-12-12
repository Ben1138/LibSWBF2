#include "pch.h"
#include "Logging/Logger.h"
#include "DirectX/DXHelpers.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "SCOP.h"
#include <algorithm>
#include <cstring>
#include <iostream>


namespace LibSWBF2::Chunks::LVL::config
{
    void SCOP::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void SCOP::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void SCOP::ReadFromStream(FileReader& stream)
    { 
        BaseChunk::ReadFromStream(stream);
        Check(stream);
        
        while (ThereIsAnother(stream))
        {
            ChunkHeader next = stream.ReadChunkHeader(true);

            if (next == "DATA"_h)
            {
                DATA_CONFIG* data;
                READ_CHILD(stream, data);
            }
            else if (next == "SCOP"_h)
            {
                SCOP* scop;
                READ_CHILD(stream, scop);
            }
            else 
            {
                READ_CHILD_GENERIC(stream);
            }
        }

        BaseChunk::EnsureEnd(stream);        
    }
}
