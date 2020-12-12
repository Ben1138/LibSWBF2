#include "stdafx.h"
#include "SMNA.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	void SMNA::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void SMNA::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void SMNA::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		m_Unknown1 = stream.ReadUInt32();
		m_Unknown2 = stream.ReadUInt32();
		m_Unknown3 = stream.ReadUInt32();
		m_NumAnimations = stream.ReadUInt16();

		m_DebugLevel = stream.ReadUInt16();

		BaseChunk::EnsureEnd(stream);
	}

	String SMNA::ToString()
	{
		return fmt::format(
			"Unknown 1: {}\n"
			"Unknown 2: {}\n"
			"Unknown 3: {}\n"
			"Num Animations: {}",
			m_Unknown1,
			m_Unknown2,
			m_Unknown3,
			m_NumAnimations
		).c_str();
	}
}