#include <LibSWBF2/pch.h>
#include <LibSWBF2/Chunks/LVL/gmod/gmod.h>
#include "InternalHelpers.h"
#include <LibSWBF2/IO/FileReader.h>

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