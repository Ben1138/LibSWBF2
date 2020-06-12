#include "stdafx.h"
#include "inst.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
    void inst::RefreshSize()
    {
        throw std::runtime_error("Not implemented!");
    }

    void inst::WriteToStream(FileWriter& stream)
    {
        throw std::runtime_error("Not implemented!");
    }

    void inst::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        READ_CHILD(stream, p_Info);

        // TODO: get rid of this once we know all the specific chunks
		while (stream.GetFileSize() - stream.GetPosition() >= 4 && PositionInChunk(stream.GetPosition()))
		{
			GenericChunkNC* generic;
			READ_CHILD(stream, generic);
			//LOG("Found unexpected chunk in inst: " + string(generic->GetHeaderName().Buffer()) + "' at pos: " + std::to_string(stream.GetPosition()), ELogType::Warning);
		}

        BaseChunk::EnsureEnd(stream);
    }
}