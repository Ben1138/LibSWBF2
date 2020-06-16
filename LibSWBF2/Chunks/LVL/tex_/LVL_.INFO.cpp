#include "stdafx.h"
#include "tex_.h"
#include "Exceptions.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::LVL_texture
{
	void INFO::RefreshSize()
	{
		throw LibException("Not implemented!");
	}

	void INFO::WriteToStream(FileWriter& stream)
	{
		throw LibException("Not implemented!");
	}

	void INFO::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		m_MipLevel = stream.ReadUInt32();
		m_BodySize = stream.ReadUInt32();

		BaseChunk::EnsureEnd(stream);
	}

	String INFO::ToString()
	{
		return fmt::format(
			"Mip Level:\t{}\n"
			"Body Size:\t{}\n",
			m_MipLevel, m_BodySize).c_str();
	}
}