#include "stdafx.h"
#include "PTCH.h"
#include "Exceptions.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::terrain
{
    void PTCH::RefreshSize()
    {
        throw LibException("Not implemented!");
    }

    void PTCH::WriteToStream(FileWriter& stream)
    {
        throw LibException("Not implemented!");
    }

    void PTCH::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        while (ThereIsAnother(stream))
        {
            ChunkHeader next = stream.ReadChunkHeader(true);
            if (next == "VBUF"_h)
            {
                VBUF* patch;
                READ_CHILD(stream, patch);
                m_Buffers.Add(patch);
            }
            else
            {
                READ_CHILD_GENERIC(stream);
            }
        }

        BaseChunk::EnsureEnd(stream);
    }
}