#include "pch.h"
#include "StreamData.h"
#include "InternalHelpers.h"
#include "FileReader.h"


namespace LibSWBF2::Chunks::LVL::sound
{
	void StreamData::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void StreamData::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void StreamData::ReadFromStream(FileReader& stream)
	{
		SoundBaseChunk::ReadFromStream(stream);
		Check(stream);
		BaseChunk::EnsureEnd(stream);
	}
}