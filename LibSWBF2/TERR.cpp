#include "stdafx.h"
#include "TERR.h"

namespace LibSWBF2::Chunks::Terrain
{
	void TERR::WriteToStream(FileWriter& stream)
	{

	}

	void TERR::ReadFromStream(FileReader& stream)
	{
		ChunkHeader TerrHeader = stream.ReadChunkHeader(false);

		if (!TerrHeader == HeaderNames::TERR)
		{
			LOG("Wrong File Format!", ELogType::Warning);
			return;
		}

		FileVersion = stream.ReadUInt32();
		// .....
	}

	bool TERR::WriteToFile(const string& Path)
	{
		// TODO: implement
		return false;
	}

	bool TERR::ReadFromFile(const string& Path)
	{
		FileReader reader;
		if (reader.Open(Path))
		{
			try
			{
				ReadFromStream(reader);
				reader.Close();
			}
			catch (int& e)
			{
				e; // avoid C4101 warning
				LOG("Aborting read process...", ELogType::Error);
				return false;
			}
			LOG("Successfully finished reading process!", ELogType::Info);
			return true;
		}
		LOG("Could not open File " + Path + "! Non existent?", ELogType::Warning);
		return false;
	}
}