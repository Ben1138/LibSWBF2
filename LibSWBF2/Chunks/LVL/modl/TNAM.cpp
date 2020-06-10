#include "stdafx.h"
#include "TNAM.h"

namespace LibSWBF2::Chunks::LVL::modl
{
    void TNAM::RefreshSize()
    {
        throw std::runtime_error("Not implemented!");
    }

    void TNAM::WriteToStream(FileWriter& stream)
    {
        throw std::runtime_error("Not implemented!");
    }

    void TNAM::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_Index = stream.ReadUInt32();
        m_Name = stream.ReadString();

        BaseChunk::EnsureEnd(stream);
    }

    String TNAM::ToString()
    {
        return 
            "Index = " + String(std::to_string(m_Index).c_str()) + "\n" +
            "Name = " + m_Name;
    }
}