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

        // IBUFs don't have any flag of some sort. Apparently the only way
        // to distinguish a Gemoetry IBUF from a TextureExtra IBUF is the
        // chunk order. 
        // The Geometry IBUF chunk comes right after the Geometry VBUF,
        // same for TextureExtra IBUF
        static ETerrainBufferType lastVBUFType;

        while (ThereIsAnother(stream))
        {
            ChunkHeader next = stream.ReadChunkHeader(true);
            if (next == "VBUF"_h)
            {
                VBUF* bufferChunk;
                READ_CHILD(stream, bufferChunk);
                
                switch (bufferChunk->m_BufferType)
                {
                    case ETerrainBufferType::Texture:
                        m_TextureBuffer = bufferChunk;
                        break;
                    case ETerrainBufferType::Geometry:
                        m_GeometryBuffer = bufferChunk;
                        break;
                    case ETerrainBufferType::TextureExtra:
                        m_TextureExtraBuffer = bufferChunk;
                        break;
                    default:
                        LOG_WARN("Unknown VBUF chunk with type: {}", TerrainBufferTypeToString(bufferChunk->m_BufferType));
                        break;
                }
                lastVBUFType = bufferChunk->m_BufferType;
            }
            else if (next == "IBUF"_h)
            {
                IBUF* bufferChunk;
                READ_CHILD(stream, bufferChunk);

                switch (lastVBUFType)
                {
                    case ETerrainBufferType::Texture:
                        LOG_WARN("Unexpected IBUF found right after Texture VBUF!");
                        break;
                    case ETerrainBufferType::Geometry:
                        m_GeometryIndexBuffer = bufferChunk;
                        break;
                    case ETerrainBufferType::TextureExtra:
                        m_TextureExtraIndexBuffer = bufferChunk;
                        break;
                    default:
                        LOG_WARN("Unknown last VBUF chunk with type: {}", TerrainBufferTypeToString(lastVBUFType));
                        break;
                }
            }
            else
            {
                READ_CHILD_GENERIC(stream);
            }
        }

        BaseChunk::EnsureEnd(stream);
    }

    String PTCH::ToString()
    {
        return fmt::format(
            "Has Texture Vertex Buffer: {}\n"
            "Has Geometry Vertex Buffer: {}\n"
            "Has Texture Extra Vertex Buffer: {}\n"
            "\n"
            "Has Geometry IndexBuffer: {}\n"
            "Has Texture Extra IndexBuffer: {}\n",
            m_TextureBuffer != nullptr ? "yes" : "no",
            m_GeometryBuffer != nullptr ? "yes" : "no",
            m_TextureExtraBuffer != nullptr ? "yes" : "no",
            m_GeometryIndexBuffer != nullptr ? "yes" : "no",
            m_TextureExtraIndexBuffer != nullptr ? "yes" : "no"
        ).c_str();
    }
}