#include "stdafx.h"
#include "SKIN.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::modl
{
    void SKIN::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void SKIN::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void SKIN::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_VertexCount = stream.ReadUInt32();
        m_Type = stream.ReadUInt32();

        if (m_Type == 1)
        {
            for (uint32_t i = 0; i < m_VertexCount; ++i)
            {
                m_BoneIndices.Add(stream.ReadByte());
            }
        }
        else
        {
            LOG_WARN("Ignore yet unsupported SKIN type {}!", m_Type);
        }

        BaseChunk::EnsureEnd(stream);
    }

    String SKIN::ToString()
    {
        std::string result = fmt::format("Number of Vertices / Bone Indices = {}\nBone Indices = [", m_VertexCount);
        for (uint32_t i = 0; i < m_VertexCount && i < m_BoneIndices.Size(); ++i)
        {
            result += fmt::format("{}, ", m_BoneIndices[i]);
        }

        result.resize(result.size() - 2);
        result += "]";
        return result.c_str();
    }
}