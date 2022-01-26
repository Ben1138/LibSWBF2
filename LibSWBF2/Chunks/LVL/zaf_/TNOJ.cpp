#include "pch.h"
#include "TNOJ.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	void TNOJ::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void TNOJ::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void TNOJ::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		m_BoneCRC = stream.ReadUInt32();

		m_BaseRotation.ReadFromStream(stream);
		m_BasePosition.ReadFromStream(stream);

		m_ParentBoneCRC = stream.ReadUInt32();

		// Once we definitively determine what the meaning 
		// and/or use of the next 2 u32s are
		// we'll read them

		BaseChunk::EnsureEnd(stream);
	}

	String TNOJ::ToString() const
	{
		return fmt::format(
			"Bone CRC: 0x{0:x}\n"
			"Base Rotation: {1}\n"
			"Base Position: {2}\n"
			"Parent Bone CRC: 0x{3:x}\n",
			m_BoneCRC,
			m_BaseRotation.ToString(),
			m_BasePosition.ToString(),
			m_ParentBoneCRC
		).c_str();
	}
}