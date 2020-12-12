#include "stdafx.h"
#include "BIN_.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	void BIN_::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void BIN_::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void BIN_::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		stream.SkipBytes(8);

		m_Unknown1 = stream.ReadUInt32();
		m_Unknown2 = stream.ReadUInt32();
		m_Unknown3 = stream.ReadUInt32();

		m_NumAnimations = stream.ReadUInt16();
		m_DebugLevel = stream.ReadUInt16();

		READ_CHILD(stream, p_AnimsMetadata);
		READ_CHILD(stream, p_JointAddresses);
		READ_CHILD(stream, p_CompressedAnimData);

		BaseChunk::EnsureEnd(stream);
	}

	String BIN_::ToString()
	{
		return fmt::format(
			"Unknown 1: {}\n"
			"Unknown 2: {}\n"
			"Unknown 3: {}\n"
			"Num Animations: {}\n"
			"Debug Level: {}",
			m_Unknown1,
			m_Unknown2,
			m_Unknown3,
			m_NumAnimations,
			m_DebugLevel
		).c_str();
	}
}