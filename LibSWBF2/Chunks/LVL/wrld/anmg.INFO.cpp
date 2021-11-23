#include "pch.h"
#include "anmg.INFO.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
    void anmg_INFO::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void anmg_INFO::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void anmg_INFO::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_Name = stream.ReadString();

        m_0 = stream.ReadByte();
        m_1 = stream.ReadByte();

        BaseChunk::EnsureEnd(stream);
    }

    String anmg_INFO::ToString() const
    {
        String rep = fmt::format("Name: {}, Field1: {}, Field2: {}", 
                        m_Name, 
                        m_0 == 1,
                        m_1 == 1).c_str();
        return rep;
    }
}