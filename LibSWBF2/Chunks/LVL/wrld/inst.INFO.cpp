#include "stdafx.h"
#include "inst.INFO.h"
#include "Exceptions.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::wrld::instance
{
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

        READ_CHILD(stream, p_Type);
        READ_CHILD(stream, p_Name);
        READ_CHILD(stream, p_XFRM);

        BaseChunk::EnsureEnd(stream);
    }
}