#include "pch.h"
#include "SoundData.h"
#include "InternalHelpers.h"
#include "FileReader.h"


namespace LibSWBF2::Chunks::LVL::sound
{
	void SoundData::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void SoundData::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void SoundData::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);
		BaseChunk::EnsureEnd(stream);
	}
}