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

        //LOG_WARN("On vbuf: numElements: {}, elementSize: {}", m_ElementCount, m_ElementSize);

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
            //I'm so far as baffled as you as to why these are so...
            //The other data stored in each element isn't garbage 
            //or all default, it is mostly patterned.  Exact 
            //pattern/meaning still unknown.
            static int KNOWN_STRENGTH_OFFSETS[] = {15, 11, 6};

            PTCH *parentPatch = dynamic_cast<PTCH*>(GetParent());
            PTCH_INFO *patchInfo = parentPatch -> p_PatchInfo;

            List<uint32_t>& slotsList = patchInfo -> m_TextureSlotsUsed;
            int numSlotsUsed = (int) slotsList.Size();
            
            //Temp buffer for storing each raw (usually 16 byte long)
            //VBUF element
            uint8_t *elementBuffer = new uint8_t[m_ElementSize]();

            for (int i = 0; i < m_ElementCount * numSlotsUsed; i += numSlotsUsed)
            {
                stream.ReadBytes(elementBuffer, m_ElementSize);

                for (int j = 0; j < numSlotsUsed; j++)
                {                 
                    //Don't know how > 3 strengths are stored per VBUF element just yet
                    int newElement = j < 3 ? elementBuffer[KNOWN_STRENGTH_OFFSETS[j]] : 0;
                    m_BlendMapData.Add(newElement);
                }
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