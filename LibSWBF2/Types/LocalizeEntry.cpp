#include "stdafx.h"
#include "LocalizeEntry.h"
#include "InternalHelpers.h"
#include "FileWriter.h"
#include "FileReader.h"

namespace LibSWBF2::Types
{
	void LocalizeEntry::RefreshSize()
	{
		m_EntrySize = (uint8_t)(m_WideString.Size() * sizeof(Widechar) + 6);
	}

	void LocalizeEntry::WriteToStream(FileWriter& stream)
	{
		stream.WriteUInt16(m_LocalizePathHash);
		stream.WriteUInt16(m_EntrySize);
		stream.WriteBytes((uint8_t*)m_WideString.GetArrayPtr(), m_WideString.Size() * sizeof(Widechar));
	}

	void LocalizeEntry::ReadFromStream(FileReader& stream)
	{
		m_LocalizePathHash = stream.ReadUInt32();
		m_EntrySize = stream.ReadUInt16();

		int numWideChars = (m_EntrySize - 6) / 2;
		if (numWideChars <= 0)
		{
			// stop right here if there's nothing to read
			return;
		}

		m_WideString.Resize(numWideChars);
		for (int i = 0; i < numWideChars; ++i)
		{
			m_WideString.Add(stream.ReadUInt16());
		}
	}

	//String LocalizeEntry::ToString()
	//{
	//	return fmt::format(
	//		"Localize Path Hash: {}\n"
	//		"Entry Size: {}\n"
	//		"Wide String: {}",
	//		m_LocalizePathHash,
	//		m_EntrySize,
	//		(const char*)m_WideString.GetArrayPtr()
	//	).c_str();
	//}
}