#include "stdafx.h"
#include "anmg.h"
#include "Logging/Logger.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
    void anmg::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void anmg::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void anmg::ReadFromStream(FileReader& stream)
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
            else if (next == "ANIM"_h)
            {
                READ_CHILD(stream, m_AnimObjectPairs.Emplace());
            }
            else
            {
                READ_CHILD_GENERIC(stream);
            }
		}

        BaseChunk::EnsureEnd(stream);
    }
}