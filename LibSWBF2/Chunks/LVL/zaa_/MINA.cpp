#include "stdafx.h"
#include "MINA.h"
#include "BIN_.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	void MINA::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void MINA::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void MINA::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		BIN_ *desc = dynamic_cast<BIN_*>(GetParent());

		for (int i = 0; i < desc -> m_NumAnimations; i++)
		{
			m_TransBitFlags.Add(stream.ReadUInt32());
			stream.SkipBytes(4);
			m_AnimNameHashes.Add(stream.ReadUInt32());
			m_AnimFrameCounts.Add(stream.ReadUInt16());
			m_AnimBoneCounts.Add(stream.ReadUInt16());
		}

		BaseChunk::EnsureEnd(stream);
	}

	String MINA::ToString() const
	{
		String rep = String("");

		for (int i = 0; i < m_AnimNameHashes.Size(); i++)
		{
			rep = rep + fmt::format(
					"\n\nAnim name crc: {}\n"
					"\tTransBitFlags: {}\n"
					"\tNum frames: {}\n"
					"\tNum bones: {}\n",
					m_AnimNameHashes[i],
					m_TransBitFlags[i],
					m_AnimFrameCounts[i],
					m_AnimBoneCounts[i]
				).c_str();
		}

		return rep;
	}
}