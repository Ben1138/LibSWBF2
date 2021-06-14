#include "stdafx.h"
#include "BMAP.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::modl
{
    void BMAP::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void BMAP::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void BMAP::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_IndexCount = stream.ReadUInt32();
        for (uint32_t i = 0; i < m_IndexCount; ++i)
        {
            m_IndexMap.Add(stream.ReadByte());
        }

        BaseChunk::EnsureEnd(stream);
    }

    String BMAP::ToString() const
    {
        std::string result = fmt::format("Index Map Count = [", m_IndexCount);
        for (uint32_t i = 0; i < m_IndexCount; ++i)
        {
            result += fmt::format("{}, ", m_IndexMap[i]);
        }

        result.resize(result.size() - 2);
        result += "]";
        return result.c_str();
    }
}