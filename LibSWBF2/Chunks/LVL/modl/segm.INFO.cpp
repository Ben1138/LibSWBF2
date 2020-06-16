#include "stdafx.h"
#include "segm.INFO.h"
#include "Exceptions.h"
#include "FileReader.h"


namespace LibSWBF2::Chunks::LVL::modl::segment
{
	EModelPurpose INFO::GetPurpose()
	{
		return EModelPurpose::Mesh_Regular;
	}

    void INFO::RefreshSize()
    {
        throw LibException("Not implemented!");
    }

    void INFO::WriteToStream(FileWriter& stream)
    {
        throw LibException("Not implemented!");
    }

    void INFO::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_Topology = (ETopology)stream.ReadInt32();
        m_VertexCount = stream.ReadUInt32();
        m_PrimitiveCount = stream.ReadUInt32();

        BaseChunk::EnsureEnd(stream);
    }

    String INFO::ToString()
    {
        return
            "Topology = " + TopologyToString(m_Topology) + "\n" +
            "Vertex Count = " + std::to_string(m_VertexCount).c_str() + "\n" +
            "Primitive Count = " + std::to_string(m_PrimitiveCount).c_str();
    }
}