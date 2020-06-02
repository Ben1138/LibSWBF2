#include "stdafx.h"
#include "modl.segm.h"

namespace LibSWBF2::Chunks::LVL::modl
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

        while (PositionInChunk(stream.GetPosition()))
        {
            ChunkHeader next = stream.ReadChunkHeader(true);
            if (next == "INFO"_h)
            {
                READ_CHILD(stream, p_Info);
            }
            else if (next == "MTRL"_h)
            {
                READ_CHILD(stream, p_Material);
            }
            else
            {
                SkipChunk(stream, false);
            }
        }

        BaseChunk::EnsureEnd(stream);
    }
}