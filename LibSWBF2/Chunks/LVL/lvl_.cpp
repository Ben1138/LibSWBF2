#include "stdafx.h"
#include "lvl_.h"
#include "Exceptions.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL
{
    void lvl_::RefreshSize()
    {
        throw LibException("Not implemented!");
    }

    void lvl_::WriteToStream(FileWriter& stream)
    {
        throw LibException("Not implemented!");
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