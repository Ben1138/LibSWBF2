#include "stdafx.h"
#include "inst.h"
#include "Logging/Logger.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
    void inst::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void inst::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void inst::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_OverrideProperties.Clear();
		while (ThereIsAnother(stream))
		{
            ChunkHeader next = stream.ReadChunkHeader(true);
            if (next == "INFO"_h)
            {
                READ_CHILD(stream, p_Info);
            }
            else if (next == "PROP"_h)
            {
                PROP* prop;
                READ_CHILD(stream, prop);
                m_OverrideProperties.Add(prop);
            }
            else
            {
                READ_CHILD_GENERIC(stream);
            }
		}

        BaseChunk::EnsureEnd(stream);
    }
}