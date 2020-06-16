#include "stdafx.h"
#include "IBUF.h"
#include "Exceptions.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::modl
{
    void IBUF::RefreshSize()
    {
        throw LibException("Not implemented!");
    }

    void IBUF::WriteToStream(FileWriter& stream)
    {
        throw LibException("Not implemented!");
    }

    void IBUF::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_IndicesCount = stream.ReadUInt32();
        m_Indices.Resize(m_IndicesCount);
        for (uint32_t i = 0; i < m_IndicesCount; ++i)
        {
            m_Indices.Add(stream.ReadUInt16());
        }

        BaseChunk::EnsureEnd(stream);
    }

    String IBUF::ToString()
    {
        std::string result = fmt::format("Number of Inidces = {}\nIndices = [", m_IndicesCount);
        for (uint32_t i = 0; i < m_IndicesCount; ++i)
        {
            result += fmt::format("{}, ", m_Indices[i]);
        }

        result.resize(result.size() - 2);
        result += "]";
        return result.c_str();
    }
}