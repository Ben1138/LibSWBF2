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

		//Skip SMNA
		stream.SkipBytes(8);

		m_Version = stream.ReadUInt32();
		m_NumBones = stream.ReadUInt32();
		m_DataBufferLength = stream.ReadUInt32();

		m_NumAnimations = stream.ReadUInt16();
		m_DebugLevel = stream.ReadUInt16();

		if (m_DebugLevel != 0 || m_Version != 8)
		{
			while (ThereIsAnother(stream))
			{
				READ_CHILD_GENERIC(stream);
			}			
		}
		else
		{
			READ_CHILD(stream, p_AnimsMetadata);
			READ_CHILD(stream, p_JointAddresses);
			READ_CHILD(stream, p_CompressedAnimData);
		}

		BaseChunk::EnsureEnd(stream);
	}

	String BIN_::ToString()
	{
		return fmt::format(
			"Chunk version: {}\n"
			"Num bones: {}\n"
			"Compressed anim data length: {}\n"
			"Num Animations: {}\n"
			"Debug Level: {}",
			m_Version,
			m_NumBones,
			m_DataBufferLength,
			m_NumAnimations,
			m_DebugLevel
		).c_str();
	}
}