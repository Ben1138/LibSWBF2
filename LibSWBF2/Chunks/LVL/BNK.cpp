#include "stdafx.h"
#include "BNK.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL
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

		BaseChunk::EnsureEnd(stream);
	}

	String BNK::ToString()
	{
		return m_SoundBank.ToString();
	}
}