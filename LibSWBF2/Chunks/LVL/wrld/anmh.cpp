#include "pch.h"
#include "anmh.h"
#include "anmh.INFO.h"
#include "Logging/Logger.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
    void anmh::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void anmh::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void anmh::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

		while (ThereIsAnother(stream))
		{
            ChunkHeader next = stream.ReadChunkHeader(true);
            if (next == "INFO"_h)
            {
                READ_CHILD(stream, p_Info);
            }
            else
            {
                READ_CHILD_GENERIC(stream);
            }
		}

        BaseChunk::EnsureEnd(stream);
    }
}