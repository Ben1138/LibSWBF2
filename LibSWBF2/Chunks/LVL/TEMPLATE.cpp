#include "stdafx.h"
#include "segm.h"

namespace LibSWBF2::Chunks::LVL
{
    void segm::RefreshSize()
    {
        throw std::runtime_error("Not implemented!");
    }

    void segm::WriteToStream(FileWriter& stream)
    {
        throw std::runtime_error("Not implemented!");
    }

    void segm::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        BaseChunk::EnsureEnd(stream);
    }
}