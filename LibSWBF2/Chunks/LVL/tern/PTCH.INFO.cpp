#include "stdafx.h"
#include "PTCH.INFO.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::terrain
{
    void PTCH_INFO::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void PTCH_INFO::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void PTCH_INFO::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);
      
        uint32_t numTextureSlotsUsed = (uint32_t) stream.ReadByte();
        //LOG_WARN("READING PATCH INFO ... numTextureSlotsUsed {}", numTextureSlotsUsed);

        for (uint32_t i = 0; i < numTextureSlotsUsed; i++)
        {
            uint32_t texIndex = (uint32_t) stream.ReadByte();
            m_TextureSlotsUsed.Add(texIndex);
        } 

        //stream.ReadUInt32(); //IDK what this int means yet
        //m_ElementSize = stream.ReadUInt32();
        m_ElementSize = 16; //this is overwhelmingly common, stubbing it for now...

        BaseChunk::EnsureEnd(stream);
    }

    String PTCH_INFO::ToString()
    {
        std::string str_TextureSlotsUsed = "";

        for (uint32_t i = 0; i < m_TextureSlotsUsed.Size(); i++)
        {
            str_TextureSlotsUsed += std::to_string(m_TextureSlotsUsed[i]);
            str_TextureSlotsUsed += ", ";
        }

        std::string result = fmt::format(
            "Element Size: {}\nTexture slots used: {}\n", 
            m_ElementSize, 
            str_TextureSlotsUsed
        );

        return result.c_str();
    }
}