#include "pch.h"
#include "SampleBank.h"
#include "SampleBankInfo.h"
#include "InternalHelpers.h"
#include "FileReader.h"


namespace LibSWBF2::Chunks::LVL::sound
{
	void SampleBank::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void SampleBank::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void SampleBank::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		while (ThereIsAnother(stream))
		{
			ChunkHeader next = stream.ReadChunkHeader(true);
			if (next == "Info"_fnvh)
			{
				READ_CHILD(stream, p_Info);
			}
			else if (next == "Data"_fnvh)
			{
				READ_CHILD(stream, p_Data);
			}
			else 
			{
				stream.SkipBytes(4);
			}
		}

		BaseChunk::EnsureEnd(stream);
	}

	String SampleBank::ToString() const
	{
		return p_Info == nullptr ? "No info chunk found" : p_Info -> HeaderToString();
	}
}