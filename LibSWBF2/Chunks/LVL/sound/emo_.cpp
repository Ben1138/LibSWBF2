#include "stdafx.h"
#include "emo_.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::sound
{
	void emo_::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void emo_::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void emo_::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		m_SoundBank.ReadFromStream(stream);

		BaseChunk::EnsureEnd(stream);
	}

	String emo_::ToString()
	{
		return m_SoundBank.ToString();
	}
}