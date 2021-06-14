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

        for (uint32_t i = 0; i < numTextureSlotsUsed; i++)
        {
            m_TextureSlotsUsed.Add((uint32_t) stream.ReadByte());
        } 

        BaseChunk::EnsureEnd(stream);
    }

    String PTCH_INFO::ToString() const
    {
        std::string str_TextureSlotsUsed = "";

        for (uint32_t i = 0; i < m_TextureSlotsUsed.Size(); i++)
        {
            str_TextureSlotsUsed += std::to_string(m_TextureSlotsUsed[i]);
            str_TextureSlotsUsed += ", ";
        }

        std::string result = fmt::format(
            "Element Size: {}\nTexture slots used: {}\n", 
            m_TextureSlotsUsed.Size(), 
            str_TextureSlotsUsed
        );

        return result.c_str();
    }
}