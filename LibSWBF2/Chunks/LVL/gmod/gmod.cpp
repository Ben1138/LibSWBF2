#include "pch.h"
#include "gmod.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::gmod
{
    void gmod::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void gmod::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void gmod::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);
        BaseChunk::EnsureEnd(stream);
    }
}