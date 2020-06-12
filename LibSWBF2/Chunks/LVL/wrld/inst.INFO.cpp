#include "stdafx.h"
#include "inst.INFO.h"

namespace LibSWBF2::Chunks::LVL::wrld::instance
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
        Check(stream);

        READ_CHILD(stream, p_Type);
        READ_CHILD(stream, p_Name);
        READ_CHILD(stream, p_XFRM);

        BaseChunk::EnsureEnd(stream);
    }
}