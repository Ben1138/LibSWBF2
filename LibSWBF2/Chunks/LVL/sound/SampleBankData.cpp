
#include "pch.h"
#include "SampleBankData.h"
#include "SampleBank.h"
#include "SampleBankInfo.h"
#include "InternalHelpers.h"
#include "FileReader.h"


namespace LibSWBF2::Chunks::LVL::sound
{
	void SampleBankData::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void SampleBankData::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void SampleBankData::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		SampleBank *bank = dynamic_cast<SampleBank*>(GetParent());
		if (bank == nullptr)
		{
			LOG_ERROR("Tried to read SampleBankData from a chunk other than SampleBank");
		}
		else 
		{
			SampleBankInfo* info = bank -> p_Info;
			if (info == nullptr)
			{
				LOG_ERROR("Tried to read SampleBankData, but parent SampleBank's Info chunk was missing!");
			}
			else 
			{
				for (int i = 0; i < info -> m_SoundHeaders.Size(); i++)
				{
					Types::SoundClip& currClip = info -> m_SoundHeaders[i];

					size_t EndPos = stream.GetPosition() + currClip.m_DataLength + currClip.m_Padding;
					if (!PositionInChunk(EndPos))
					{
						LOG_ERROR("Attempt to read SampleBank's SoundClip data would overshoot file,...");
						break;
					}

					// If sound header has alias we skip it
					if (currClip.m_Alias != 0)
					{
						continue;
					}

					currClip.ReadDataFromStream(stream);
				}
			}
		}

		BaseChunk::EnsureEnd(stream);
	}
}
