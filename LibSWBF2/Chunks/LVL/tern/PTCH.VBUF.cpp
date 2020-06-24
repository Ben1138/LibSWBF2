#include "stdafx.h"
#include "PTCH.VBUF.h"
#include "Exceptions.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::terrain
{
    void VBUF::RefreshSize()
    {
        throw LibException("Not implemented!");
    }

    void VBUF::WriteToStream(FileWriter& stream)
    {
        throw LibException("Not implemented!");
    }

    void VBUF::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_ElementCount = stream.ReadUInt32();
        m_ElementSize = stream.ReadUInt32();
        m_BufferType = (ETerrainBufferType)stream.ReadUInt32();

        bool bAbort = false;
        if (m_ElementCount != 81)
        {
            LOG_WARN("Invalid VBUF terrain chunk found with ElementCount: %i", m_ElementCount);
            bAbort = true;
        }
        if (m_ElementSize != 28 && m_ElementSize != 16)
        {
            LOG_WARN("Invalid VBUF terrain chunk found with ElementSize: %i", m_ElementSize);
            bAbort = true;
        }

        if (!bAbort)
        {
            if (m_BufferType == ETerrainBufferType::Geometry)
            {
                for (uint32_t i = 0; i < m_ElementCount; ++i)
                {
                    m_TerrainBuffer.Emplace().ReadFromStream(stream);
                }
            }
            else
            {
                LOG_WARN("Skip yet unsupported Terrain Buffer Type: %s", TerrainBufferTypeToString(m_BufferType));
            }
        }

        BaseChunk::EnsureEnd(stream);
    }
}