#include "stdafx.h"
#include "XFRM.h"
#include "Exceptions.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
    void XFRM::RefreshSize()
    {
        throw LibException("Not implemented!");
    }

    void XFRM::WriteToStream(FileWriter& stream)
    {
        throw LibException("Not implemented!");
    }

    void XFRM::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_RotationMatrix.ReadFromStream(stream);
        m_Position.ReadFromStream(stream);

        BaseChunk::EnsureEnd(stream);
    }

    String XFRM::ToString()
    {
        return
            "Matrix 3x3: " + m_RotationMatrix.ToString() + "\n\n" +
            "Position: " + m_Position.ToString();
    }
}