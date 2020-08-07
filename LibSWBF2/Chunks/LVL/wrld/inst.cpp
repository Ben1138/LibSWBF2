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

        READ_CHILD(stream, p_Info);

        // TODO: get rid of this once we know all the specific chunks
		while (ThereIsAnother(stream))
		{
            READ_CHILD_GENERIC(stream);
		}

        BaseChunk::EnsureEnd(stream);
    }
}