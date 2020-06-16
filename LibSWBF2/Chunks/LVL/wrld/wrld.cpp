#include "stdafx.h"
#include "wrld.h"
#include "Exceptions.h"
#include "Logging/Logger.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
    void wrld::RefreshSize()
    {
        throw std::runtime_error("Not implemented!");
    }

    void wrld::WriteToStream(FileWriter& stream)
    {
        throw std::runtime_error("Not implemented!");
    }

    void wrld::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        READ_CHILD(stream, p_Name);

		// since in wrld, some chunks are optional, we have to crawl dynamically
		while (stream.GetFileSize() - stream.GetPosition() >= 4 && PositionInChunk(stream.GetPosition()))
		{
			ChunkHeader nextHead = stream.ReadChunkHeader(true);
			if (nextHead == "TNAM"_h)
			{
				READ_CHILD(stream, p_TerrainName);
			}
			else if (nextHead == "SNAM"_h)
			{
				READ_CHILD(stream, p_SkyName);
			}
			else if (nextHead == "inst"_h)
			{
				inst* instance;
				READ_CHILD(stream, instance);
				m_Instances.Add(instance);
			}
			else
			{
				GenericChunkNC* generic;
				READ_CHILD(stream, generic);
				//LOG_WARN("Found unexpected chunk in wrld: '{}' at pos: {}", nextHead, stream.GetPosition());
			}
		}

        BaseChunk::EnsureEnd(stream);
    }
}