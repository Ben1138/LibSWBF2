#include "stdafx.h"
#include "PTCH.VBUF.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::terrain
{
    void VBUF::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void VBUF::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void VBUF::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_ElementCount = stream.ReadUInt32();
        m_ElementSize = stream.ReadUInt32();
        m_BufferType = (ETerrainBufferType)stream.ReadUInt32();

        if (m_BufferType == ETerrainBufferType::Geometry)
        {
            //if (m_ElementCount != 81)
            //{
            //    LOG_WARN("Invalid geometry VBUF terrain chunk found with ElementCount: {}", m_ElementCount);
            //}
            //else if (m_ElementSize != 28 && m_ElementSize != 16)
            //{
            //    LOG_WARN("Invalid geometry VBUF terrain chunk found with ElementSize: {}", m_ElementSize);
            //}
            //else
            //{
                for (uint32_t i = 0; i < m_ElementCount; ++i)
                {
                    m_TerrainBuffer.Emplace().ReadFromStream(stream);
                }
            //}
        }
        else if (m_BufferType == ETerrainBufferType::Texture)
        {
            static int tstvar = 0;
            static uint8_t biggerInt = 0;

            LOG_WARN("Element size: {} Element count: {}", m_ElementSize, m_ElementCount);

            p_SplatMapData = new uint8_t[ m_ElementSize * m_ElementCount ]();

            for (uint32_t i = 0; i < m_ElementCount * m_ElementSize; i+=m_ElementSize)
            {
                int j = (int) i / 4;

                

                p_SplatMapData[j] = biggerInt * 10;//stream.ReadByte();
                p_SplatMapData[j + 1] = biggerInt * 10;//stream.ReadByte();
                p_SplatMapData[j + 2] = biggerInt * 10;//stream.ReadByte();
                p_SplatMapData[j + 3] = biggerInt * 10;//stream.ReadByte();
                stream.SkipBytes(m_ElementSize - 4);
            }

            biggerInt++;
        }
        else
        {
            LOG_INFO("Skip yet unsupported Terrain Buffer Type: {}", TerrainBufferTypeToString(m_BufferType));
        }

        BaseChunk::EnsureEnd(stream);
    }

    String VBUF::ToString()
    {
        std::string result = fmt::format(
            "Element Count: {}\n"
            "Element Size: {}\n"
            "Buffer Type: {}\n"
            "\n"
            "Buffer: \n\n",
            m_ElementCount,
            m_ElementSize,
            TerrainBufferTypeToString(m_BufferType)
        );

        for (uint32_t i = 0; i < m_TerrainBuffer.Size(); ++i)
        {
            result += m_TerrainBuffer[i].ToString().Buffer();
            result += "\n\n";
        }

        return result.c_str();
    }
}