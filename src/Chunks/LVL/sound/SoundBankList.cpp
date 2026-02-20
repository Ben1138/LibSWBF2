#include <LibSWBF2/pch.h>
#include <LibSWBF2/Chunks/LVL/sound/SoundBankList.h>
#include <LibSWBF2/Chunks/LVL/sound/SampleBank.h>
#include <LibSWBF2/IO/FileReader.h>
#include "InternalHelpers.h"
#include <LibSWBF2/Hashing.h>


namespace LibSWBF2::Chunks::LVL::sound
{
	void SoundBankList::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void SoundBankList::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void SoundBankList::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		while (ThereIsAnother(stream))
		{
			ChunkHeader next = stream.ReadChunkHeader(true);
			if (next == "SampleBank"_fnvh)
			{
				READ_CHILD(stream, m_SampleBanks.Emplace())
			}
			else 
			{
				stream.SkipBytes(4);
			}		
		}

		BaseChunk::EnsureEnd(stream);
	}

	String SoundBankList::ToString() const
	{
		std::string result = fmt::format(
			"Num sample banks: {0}",
			m_SampleBanks.Size()
		);

		return result.c_str();
	}
}