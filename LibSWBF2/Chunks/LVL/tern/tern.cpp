#include "stdafx.h"
#include "tern.h"
#include "Exceptions.h"
#include "FileReader.h"
#include <fmt/format.h>

namespace LibSWBF2::Chunks::LVL
{
    void tern::RefreshSize()
    {
        throw LibException("Not implemented!");
    }

    void tern::WriteToStream(FileWriter& stream)
    {
        throw LibException("Not implemented!");
    }

    void tern::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        while (PositionInChunk(stream.GetPosition()))
        {
            ChunkHeader next = stream.ReadChunkHeader(true);
            if (next == "NAME"_h)
            {
                READ_CHILD(stream, p_Name);
            }
            else if (next == "INFO"_h)
            {
                READ_CHILD(stream, p_Info);
            }
            else if (next == "PCHS"_h)
            {
                READ_CHILD(stream, p_Patches);
            }
            else
            {
                SkipChunk(stream, false);
            }
        }

        BaseChunk::EnsureEnd(stream);
    }

    String tern::ToString()
    {
        return fmt::format("Name: %s", p_Name->m_Text).c_str();
    }
}