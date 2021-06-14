#include "stdafx.h"
#include "Locl.BODY.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include <string>

namespace LibSWBF2::Chunks::LVL::Localization
{
    void BODY::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void BODY::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void BODY::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        // Use PositionInChunk instead of ThereIsAnother here,
        // since we're reading raw data and no chunks
        while (PositionInChunk(stream.GetPosition()))
        {
            LocalizeEntry entry;
            entry.ReadFromStream(stream);
            if (entry.m_LocalizePathHash == 0)
            {
                break;
            }

            m_LocalizeEntries.Add(entry);
        }

        BaseChunk::EnsureEnd(stream);       
    }

    String BODY::ToString() const
    {
        //std::string result;
        //for (size_t i = 0; i < m_LocalizeEntries.Size(); ++i)
        //{
        //    result += m_LocalizeEntries[i].ToString().Buffer();
        //    result += "\n\n";
        //}
        //return result.c_str();
        return fmt::format("Number of entries: {}", (uint32_t)m_LocalizeEntries.Size()).c_str();
    }
}