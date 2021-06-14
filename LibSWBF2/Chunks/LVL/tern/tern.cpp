#include "stdafx.h"
#include "tern.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include <fmt/format.h>

namespace LibSWBF2::Chunks::LVL::terrain
{
    void tern::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void tern::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
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
            else if (next == "DTLX"_h)
            {
                READ_CHILD(stream, p_DetailTexture);
            }
            else if (next == "INFO"_h)
            {
                READ_CHILD(stream, p_Info);
            }
            else if (next == "LTEX"_h)
            {
                READ_CHILD(stream, p_LayerTextures);
            }
            else if (next == "DTEX"_h)
            {
                READ_CHILD(stream, p_LayerDetailTextures);
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

    String tern::ToString() const
    {
        return fmt::format("Name: {}", p_Name->m_Text).c_str();
    }
}