#include "stdafx.h"
#include "INFO.h"

namespace LibSWBF2::Chunks::LVL::modl
{

    void INFO::RefreshSize()
    {
        throw std::runtime_error("Not implemented!");
    }

    void INFO::WriteToStream(FileWriter& stream)
    {
        throw std::runtime_error("Not implemented!");
    }

    void INFO::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);

        m_VertexBox[0].ReadFromStream(stream);
        m_VertexBox[1].ReadFromStream(stream);

        m_VisibilityBox[0].ReadFromStream(stream);
        m_VisibilityBox[1].ReadFromStream(stream);

        m_FaceCount = stream.ReadUInt32();

        BaseChunk::EnsureEnd(stream);
    }

    String INFO::ToString()
    {
        return
            "VertexBox[0] = " + m_VertexBox[0].ToString() + "\n" + 
            "VertexBox[1] = " + m_VertexBox[1].ToString() + "\n" +
            "VisibilityBox[0] = " + m_VisibilityBox[1].ToString() + "\n" +
            "VisibilityBox[1] = " + m_VisibilityBox[1].ToString() + "\n" +
            "FaceCount = " + std::to_string(m_FaceCount).c_str();
    }
}