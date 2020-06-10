#include "stdafx.h"
#include "lvl_.h"

namespace LibSWBF2::Chunks::LVL
{
    void lvl_::RefreshSize()
    {
        throw std::runtime_error("Not implemented!");
    }

    void lvl_::WriteToStream(FileWriter& stream)
    {
        throw std::runtime_error("Not implemented!");
    }

    void lvl_::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_NameHash = stream.ReadUInt32();
        m_SizeLeft = stream.ReadUInt32();

        ReadGenerics(stream);

        BaseChunk::EnsureEnd(stream);
    }
}