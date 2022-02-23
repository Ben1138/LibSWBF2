#include "pch.h"
#include "anim.INFO.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
    void anim_INFO::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void anim_INFO::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void anim_INFO::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_Name = stream.ReadString();

        m_RunTime = stream.ReadFloat();
        m_Looping = stream.ReadByte();
        m_LocalTranslation = stream.ReadByte();

        BaseChunk::EnsureEnd(stream);
    }

    String anim_INFO::ToString() const
    {
        String rep = fmt::format("Name: {}, Run Time: {}, Is Looping: {}, Transition Is Local: {}", 
                        m_Name, 
                        m_RunTime,
                        m_Looping == 1,
                        m_LocalTranslation == 1).c_str();
        return rep;
    }
}