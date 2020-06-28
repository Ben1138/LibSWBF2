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

        while (ThereIsAnother(stream))
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
                READ_CHILD_GENERIC(stream);
            }
        }

        BaseChunk::EnsureEnd(stream);
    }

    String PCHS::ToString()
    {
        return fmt::format("Num Patches: {}", m_Patches.Size()).c_str();
    }
}