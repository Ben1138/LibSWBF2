#include "pch.h"
#include "anmh.INFO.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
    void anmh_INFO::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void anmh_INFO::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void anmh_INFO::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_NumStrings = stream.ReadByte();

        for (int i = 0; i < (int) m_NumStrings; i++)
        {
            String newStr = stream.ReadString();
            if (i == 0)
            {
                m_RootName = newStr;
            }
            else 
            {
                m_ChildNames.Add(newStr);
            }
        }

        BaseChunk::EnsureEnd(stream);
    }

    String anmh_INFO::ToString() const
    {
        if (m_NumStrings == 0)
        {
            return "Empty Hierarchy";
        }
        else 
        {
            String rep = fmt::format("Root: {} ", m_Name).c_str();   
            for (int i = 0; i < m_ChildNames.Size(); i++)
            {
                rep = rep + fmt::format("\n  Child {0}: {1}", i, m_ChildNames[i]).c_str()
            }  

            return rep;       
        }
    }
}