#include "stdafx.h"
#include "IBUF.h"

namespace LibSWBF2::Chunks::LVL::modl
{
    void IBUF::RefreshSize()
    {
        throw std::runtime_error("Not implemented!");
    }

    void IBUF::WriteToStream(FileWriter& stream)
    {
        throw std::runtime_error("Not implemented!");
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
        string result = string("Number of Inidces = ") + std::to_string(m_IndicesCount).c_str() + "\nIndices = [";
        for (uint32_t i = 0; i < m_IndicesCount; ++i)
        {
            result += std::to_string(m_Indices[i]).c_str() + string(", ");
        }

        result.resize(result.size() - 2);
        result += "]";
        return result.c_str();
    }
}