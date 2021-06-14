#include "stdafx.h"
#include "INFO.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::modl
{
    void INFO::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void INFO::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void INFO::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_Unknown[0] = stream.ReadUInt32();
        m_Unknown[1] = stream.ReadUInt32();
        m_Unknown[2] = stream.ReadUInt32();
        m_Unknown[3] = stream.ReadUInt32();

        m_VertexBox[0].ReadFromStream(stream);
        m_VertexBox[1].ReadFromStream(stream);

        m_VisibilityBox[0].ReadFromStream(stream);
        m_VisibilityBox[1].ReadFromStream(stream);

        m_Unknown[4] = stream.ReadUInt32();

        m_FaceCount = stream.ReadUInt32();

        BaseChunk::EnsureEnd(stream);
    }

    String INFO::ToString() const
    {
        return
            "VertexBox[0] = " + m_VertexBox[0].ToString() + "\n" + 
            "VertexBox[1] = " + m_VertexBox[1].ToString() + "\n" +
            "VisibilityBox[0] = " + m_VisibilityBox[1].ToString() + "\n" +
            "VisibilityBox[1] = " + m_VisibilityBox[1].ToString() + "\n" +
            "FaceCount = " + std::to_string(m_FaceCount).c_str();
    }
}