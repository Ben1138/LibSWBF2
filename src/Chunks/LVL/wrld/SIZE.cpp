#include <LibSWBF2/pch.h>
#include <LibSWBF2/Chunks/LVL/wrld/SIZE.h>
#include <LibSWBF2/Logging/Logger.h>
#include "InternalHelpers.h"
#include <LibSWBF2/IO/FileReader.h>

namespace LibSWBF2::Chunks::LVL::wrld
{
    void SIZE::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void SIZE::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void SIZE::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_Dimensions.ReadFromStream(stream);

        BaseChunk::EnsureEnd(stream);
    }

    String SIZE::ToString() const
    {
        return m_Dimensions.ToString();
    }
}