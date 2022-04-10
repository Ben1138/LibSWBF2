#include "pch.h"
#include "plan.h"
#include "FileReader.h"
#include "InternalHelpers.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"
#include "Types/List.h"

#define NAME_LENGTH 16

void LibSWBF2::Chunks::plan::PLAN_INFO::ReadFromStream(FileReader& stream)
{
    BaseChunk::ReadFromStream(stream);
    Check(stream);

    m_iHubCount = stream.ReadInt16();
    m_iConnectionCount = stream.ReadInt16();

    BaseChunk::EnsureEnd(stream);
}


String LibSWBF2::Chunks::plan::PLAN_INFO::ToString() const
{
    return fmt::format("Hub count: {0}, Connection count: {1}", 
                    m_iHubCount, m_iConnectionCount).c_str();
}



void LibSWBF2::Chunks::plan::plan::ReadFromStream(FileReader& stream)
{
    BaseChunk::ReadFromStream(stream);
    Check(stream);

    ChunkHeader nextHeader;

    while (ThereIsAnother(stream))
    {
        nextHeader = stream.ReadChunkHeader(true);

        if (nextHeader == "INFO"_h)
        {
            READ_CHILD(stream, m_pInfo);
        }
        else if (nextHeader == "NODE"_h)
        {
            m_pNode = new NODE(m_pInfo->m_iHubCount);
            ReadExplicitNoCtor(this, stream, m_pNode);
        }
        else if (nextHeader == "ARCS"_h)
        {
            m_pArcs = new ARCS(m_pInfo->m_iConnectionCount);
            ReadExplicitNoCtor(this, stream, m_pArcs);
        }
        else
        {
            READ_CHILD_GENERIC(stream);
        }
    }

    BaseChunk::EnsureEnd(stream);
}

void LibSWBF2::Chunks::plan::NODE::ReadFromStream(FileReader& stream)
{
    BaseChunk::ReadFromStream(stream);
    Check(stream);

    for (int i = 0; i < m_iCount; i++)
    {
        m_aHubs.Emplace().ReadFromStream(stream, m_iCount);
    }

    BaseChunk::EnsureEnd(stream);
}

LibSWBF2::Chunks::plan::NODE::NODE(uint16_t count)
    : m_iCount(count)
{
}


String LibSWBF2::Chunks::plan::NODE::ToString() const
{
    String rep = fmt::format("{0} hubs:\n", m_iCount).c_str();
    for (int i = 0; i < m_aHubs.Size(); i++)
    {
        rep = "  " + rep + m_aHubs[i].ToString().Buffer() + "\n";
    }
    return rep;
}



void LibSWBF2::Chunks::plan::ARCS::ReadFromStream(FileReader& stream)
{
    BaseChunk::ReadFromStream(stream);
    Check(stream);

    for (int i = 0; i < m_iCount; i++)
    {
        m_aConnections.Emplace().ReadFromStream(stream);
    }

    BaseChunk::EnsureEnd(stream);
}

LibSWBF2::Chunks::plan::ARCS::ARCS(uint16_t count)
    : m_iCount(count)
{
}


String LibSWBF2::Chunks::plan::ARCS::ToString() const
{
    String rep = fmt::format("{0} connections:\n", m_iCount).c_str();
    for (int i = 0; i < m_aConnections.Size(); i++)
    {
        rep = "  " + rep + m_aConnections[i].ToString().Buffer() + "\n";
    }
    return rep;
}
