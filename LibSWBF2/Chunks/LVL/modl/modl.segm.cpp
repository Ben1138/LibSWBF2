#include "stdafx.h"
#include "modl.segm.h"
#include "Exceptions.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::modl
{
    void segm::RefreshSize()
    {
        throw LibException("Not implemented!");
    }

    void segm::WriteToStream(FileWriter& stream)
    {
        throw LibException("Not implemented!");
    }

    void segm::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        while (ThereIsAnother(stream))
        {
            ChunkHeader next = stream.ReadChunkHeader(true);
            if (next == "INFO"_h)
            {
                READ_CHILD(stream, p_Info);
            }
            else if (next == "MTRL"_h)
            {
                READ_CHILD(stream, p_Material);
            }
            else if (next == "RTYP"_h)
            {
                READ_CHILD(stream, p_RenderType);
            }
            else if (next == "IBUF"_h)
            {
                READ_CHILD(stream, p_IndexBuffer);
            }
            else if (next == "BNAM"_h)
            {
                READ_CHILD(stream, p_Parent);
            }
            else if (next == "VBUF"_h)
            {
                VBUF* vertexBuffer;
                READ_CHILD(stream, vertexBuffer);
                m_VertexBuffers.Add(vertexBuffer);
            }
            else if (next == "TNAM"_h)
            {
                TNAM* texture;
                READ_CHILD(stream, texture);
                m_Textures.Add(texture);
            }
            else
            {
                READ_CHILD_GENERIC(stream);
            }
        }

        BaseChunk::EnsureEnd(stream);
    }
}