#include "stdafx.h"
#include "LVL.h"

namespace LibSWBF2::Chunks::LVL
{
	LVL* LVL::Create()
	{
		return new LVL();
	}

	void LVL::Destroy(LVL* lvl)
	{
		delete lvl;
	}

	void LVL::ReadFromStream(FileReader& stream)
	{
		ChunkHeader head = stream.ReadChunkHeader(true);
		if (head != HeaderNames::ucfb)
		{
			LOG("This is not a valid LVL file!", ELogType::Error);
			return;
		}

		GenericChunk::ReadFromStream(stream);
	}
}