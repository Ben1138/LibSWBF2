#include "pch.h"
#include "TerrainBufferEntry.h"
#include "InternalHelpers.h"
#include "FileWriter.h"
#include "FileReader.h"
#include <algorithm>
#include <fmt/format.h>

namespace LibSWBF2::Types
{
	void TerrainBufferEntry::WriteToStream(FileWriter& stream)
	{
		m_Position.WriteToStream(stream);
		m_Normal.WriteToStream(stream);
		m_Color.WriteToStream(stream);
	}

	void TerrainBufferEntry::ReadFromStream(FileReader& stream)
	{
		m_Position.ReadFromStream(stream);
		m_Normal.ReadFromStream(stream);
		m_Color.ReadFromStream(stream);
	}

	String TerrainBufferEntry::ToString() const
	{
		return fmt::format(
			"Position: {}\n"
			"Normal: {}\n"
			"Color: {}",
			m_Position.ToString(),
			m_Normal.ToString(),
			m_Color.ToString()
		).c_str();
	}
}