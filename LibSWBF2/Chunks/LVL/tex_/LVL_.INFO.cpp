#include "stdafx.h"
#include "tex_.h"

namespace LibSWBF2::Chunks::LVL::LVL_texture
{
	void INFO::RefreshSize()
	{
		throw std::runtime_error("Not implemented!");
	}

	void INFO::WriteToStream(FileWriter& stream)
	{
		throw std::runtime_error("Not implemented!");
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
		string result = "Mip Level:\t" + std::to_string(m_MipLevel) + "\n";
		result += "Body Size:\t" + std::to_string(m_BodySize) + "\n";
		return result.c_str();
	}
}