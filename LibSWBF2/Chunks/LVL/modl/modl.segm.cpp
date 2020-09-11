#include "stdafx.h"
#include "modl.segm.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::modl
{
    void segm::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void segm::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
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
            else if (next == "SKIN"_h)
            {
                READ_CHILD(stream, p_Skin);
            }
            else if (next == "BMAP"_h)
            {
                READ_CHILD(stream, p_BoneMap);
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

        if (p_Skin != nullptr && p_BoneMap == nullptr)
        {
            // does this ever exist?
            LOG_WARN("Found model segment (segm) with SKIN, but without BMAP! Chunk pos: {:#x}", GetPosition());
        }

        BaseChunk::EnsureEnd(stream);
    }
}