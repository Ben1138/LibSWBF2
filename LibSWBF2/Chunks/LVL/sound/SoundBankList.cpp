#include "pch.h"
#include "SoundBankList.h"
#include "FileReader.h"
#include "InternalHelpers.h"
#include "Hashing.h"

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
		SoundBaseChunk::ReadFromStream(stream);
		Check(stream);

		/*
		stream.SetPosition(GetPosition() - 8);

		m_SoundBankHeader.ReadFromStream(stream);

		uint32_t i = 0;
		try
		{
			for (i = 0; i < m_SoundBankHeader.m_Clips.Size(); ++i)
			{
				m_SoundBankHeader.m_Clips[i].ReadDataFromStream(stream);
			}
		}
		catch (LibException e)
		{
			LOG_WARN("{}", e.what());
		}
		*/

		BaseChunk::EnsureEnd(stream);
	}

	String SoundBankList::ToString() const
	{
		return m_SoundBankHeader.ToString();
	}
}