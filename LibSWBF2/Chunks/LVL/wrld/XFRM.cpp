#include "pch.h"
#include "XFRM.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
    void XFRM::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void XFRM::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void XFRM::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_RotationMatrix.ReadFromStream(stream);
        m_Position.ReadFromStream(stream);

        BaseChunk::EnsureEnd(stream);
    }

    String XFRM::ToString() const
    {
        return
            "Rotation:\n" + m_RotationMatrix.ToString() + "\n\n" +
            "Position: " + m_Position.ToString();
    }
}