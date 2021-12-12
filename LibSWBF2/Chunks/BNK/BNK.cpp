#include "pch.h"
#include "BNK.h"
#include "FileReader.h"
#include "InternalHelpers.h"
#include "Hashing.h"

namespace LibSWBF2::Chunks::BNK
{
	BNK* BNK::Create()
	{
		return new BNK();
	}

	void BNK::Destroy(BNK* soundBank)
	{
		delete soundBank;
	}

	void BNK::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		m_SoundBank.ReadFromStream(stream);

		uint32_t i = 0;
		try
		{
			for (i = 0; i < m_SoundBank.m_Clips.Size(); ++i)
			{
				m_SoundBank.m_Clips[i].ReadDataFromStream(stream);
			}
		}
		catch (LibException& e)
		{
			LOG_WARN(e.what());
		}

		BaseChunk::EnsureEnd(stream);
	}

	bool BNK::TryLookupName(String& result)
	{
		return m_SoundBank.TryLookupName(result);
	}

	String BNK::ToString() const
	{
		return m_SoundBank.ToString();
	}
}