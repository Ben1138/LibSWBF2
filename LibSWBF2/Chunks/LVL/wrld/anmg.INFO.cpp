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

        m_PlayAtStart = stream.ReadByte();
        m_StopOnControl = stream.ReadByte();

        BaseChunk::EnsureEnd(stream);
    }

    String anmg_INFO::ToString() const
    {
        String rep = fmt::format("Name: {}, Is Played At Start? {}, Disabled When Controlled? {}", 
                        m_Name, 
                        m_PlayAtStart == 1,
                        m_StopOnControl == 1).c_str();
        return rep;
    }
}