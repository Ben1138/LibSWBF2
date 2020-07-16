#include "stdafx.h"
#include "wrld.h"
#include "Exceptions.h"
#include "Logging/Logger.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
    void wrld::RefreshSize()
    {
        throw LibException("Not implemented!");
    }

    void wrld::WriteToStream(FileWriter& stream)
    {
        throw LibException("Not implemented!");
    }

    void wrld::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        READ_CHILD(stream, p_Name);

		// since in wrld, some chunks are optional, we have to crawl dynamically
		while (ThereIsAnother(stream))
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
				READ_CHILD_GENERIC(stream);
			}
		}

        BaseChunk::EnsureEnd(stream);
    }

	String wrld::ToString()
	{
		return fmt::format(
			"World Name: {}\n\n"
			"Terrain Name: {}\n"
			"Sky Name: {}\n"
			"Number of object instances: {}\n",
			p_Name->m_Text,
			p_TerrainName ? p_TerrainName->m_Text : "",
			p_SkyName ? p_SkyName->m_Text : "",
			m_Instances.Size()
		).c_str();
	}
}