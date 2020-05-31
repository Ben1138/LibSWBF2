#include "stdafx.h"
#include "tex_.INFO.h"
#include "Logger.h"
#include "DXHelpers.h"

namespace LibSWBF2::Chunks::LVL::texture
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

		m_FormatCount = stream.ReadUInt32();
		for (uint32_t i = 0; i < m_FormatCount; ++i)
		{
			m_Formats.Add((D3DFORMAT)stream.ReadUInt32());
		}

		BaseChunk::EnsureEnd(stream);
	}

	String INFO::ToString()
	{
		string result = "Number of formats: " + std::to_string(m_FormatCount) + "\n";
		for (size_t i = 0; i < m_Formats.Size(); ++i)
		{
			result += "\tFormat: " + D3DToString(m_Formats[i]) + "\n";
		}
		return result.c_str();
	}
}