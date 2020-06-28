#include "stdafx.h"
#include "tern.h"
#include "Exceptions.h"
#include "FileReader.h"
#include <fmt/format.h>

namespace LibSWBF2::Chunks::LVL::terrain
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

        while (ThereIsAnother(stream))
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
                READ_CHILD_GENERIC(stream);
            }
        }

        BaseChunk::EnsureEnd(stream);
    }

    String tern::ToString()
    {
        return fmt::format("Name: {}", p_Name->m_Text).c_str();
    }
}