#include "stdafx.h"
#include "PCHS.h"
#include "Exceptions.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::terrain
{
    void PCHS::RefreshSize()
    {
        throw LibException("Not implemented!");
    }

    void PCHS::WriteToStream(FileWriter& stream)
    {
        throw LibException("Not implemented!");
    }

    void PCHS::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        while (PositionInChunk(stream.GetPosition()))
        {
            ChunkHeader next = stream.ReadChunkHeader(true);
            if (next == "PTCH"_h)
            {
                PTCH* patch;
                READ_CHILD(stream, patch);
                m_Patches.Add(patch);
            }
            else
            {
                SkipChunk(stream, false);
            }
        }

        BaseChunk::EnsureEnd(stream);
    }
}