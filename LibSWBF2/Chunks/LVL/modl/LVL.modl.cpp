#include "stdafx.h"
#include "LVL.modl.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::modl
{
    void modl::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void modl::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void modl::ReadFromStream(FileReader& stream)
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
            else if (next == "NODE"_h)
            {
                READ_CHILD(stream, p_Node);
            }
            else if (next == "INFO"_h)
            {
                READ_CHILD(stream, p_Info);
            }
            else if (next == "segm"_h)
            {
                segm* segment;
                READ_CHILD(stream, segment);
                m_Segments.Add(segment);
            }
            else
            {
                READ_CHILD_GENERIC(stream);
            }
        }

        BaseChunk::EnsureEnd(stream);
    }

    String modl::ToString()
    {
        return
            "NAME: " + p_Name->m_Text + "\n\n" +
            "INFO:\n" +
            p_Info->ToString() + "\n\n" +
            "Number of Segments: " + std::to_string(m_Segments.Size()).c_str();
    }
}