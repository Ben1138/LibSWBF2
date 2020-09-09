#include "stdafx.h"
#include "PTCH.VBUF.h"
#include "PTCH.INFO.h"
#include "PTCH.h"
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

            PTCH *parentPatch = reinterpret_cast<PTCH*>(m_Parent);
            PTCH_INFO *patchInfo = parentPatch -> p_PatchInfo;

            auto slotsList = patchInfo -> m_TextureSlotsUsed;
            int numSlotsUsed = (int) slotsList.Size();
            
            p_SplatMapData = new uint8_t[ m_ElementSize * m_ElementCount ]();

            uint8_t *elementBuffer = new uint8_t[m_ElementSize]();

            for (uint32_t i = 0; i < m_ElementCount * m_ElementSize; i+=m_ElementSize)
            {
                int j = (int) i / 4;

                stream.ReadBytes(elementBuffer, m_ElementSize);

                for (int k = 0; k < slotsList.Size(); k++)
                {
                    int slot = (int) slotsList[k];

                    if (slot > 3)
                    {
                        continue;
                    }

                    //slot = slot == 3 ? 2 : slot;

                    if (k == 0)
                    {
                        p_SplatMapData[j + slot] = elementBuffer[15];
                    }

                    if (k == 1)
                    {
                        p_SplatMapData[j + slot] = elementBuffer[11];
                    }

                    if (k == 2)
                    {
                        p_SplatMapData[j + slot] = elementBuffer[6];
                    }
                }

                p_SplatMapData[j + 3] = 255;

            }

            delete[] elementBuffer;
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