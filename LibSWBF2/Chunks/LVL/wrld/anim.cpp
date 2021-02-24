#include "stdafx.h"
#include "anim.h"
#include "Logging/Logger.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
    void anim::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void anim::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void anim::ReadFromStream(FileReader& stream)
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
            else if (next == "POSK"_h)
            {
                READ_CHILD(stream, m_PositionKeys.Emplace());
            }
            else if (next == "ROTK"_h)
            {
                READ_CHILD(stream, m_RotationKeys.Emplace());
            }
            else
            {
                READ_CHILD_GENERIC(stream);
            }
		}

        BaseChunk::EnsureEnd(stream);
    }
}