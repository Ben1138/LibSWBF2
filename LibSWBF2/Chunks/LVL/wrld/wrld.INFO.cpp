#include "pch.h"
#include "wrld.INFO.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::wrld
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

        READ_CHILD(stream, p_Type);
        READ_CHILD(stream, p_Name);
        READ_CHILD(stream, p_XFRM);

        if (ThereIsAnother(stream))
        {
            READ_CHILD(stream, p_SIZE);
        }

        BaseChunk::EnsureEnd(stream);
    }
}