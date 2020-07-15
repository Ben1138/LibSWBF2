#include "stdafx.h"
#include "tex_.INFO.h"
#include "InternalHelpers.h"
//#include "DirectX/DXHelpers.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include <fmt/format.h>

namespace LibSWBF2::Chunks::LVL::texture
{
	void INFO::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void INFO::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void INFO::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		m_FormatCount = stream.ReadUInt32();
		for (uint32_t i = 0; i < m_FormatCount; ++i)
		{
			//m_Formats.Add((D3DFORMAT)stream.ReadUInt32());
		}

		BaseChunk::EnsureEnd(stream);
	}

	String INFO::ToString()
	{
		std::string result = fmt::format("Number of formats: {}\n", m_FormatCount);
		for (size_t i = 0; i < m_Formats.Size(); ++i)
		{
			result += fmt::format("\tFormat: {}\n", ""/*D3DToString(m_Formats[i])*/);
		}
		return result.c_str();
	}
}