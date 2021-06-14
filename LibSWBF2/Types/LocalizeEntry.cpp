#include "stdafx.h"
#include "LocalizeEntry.h"
#include "InternalHelpers.h"
#include "FileWriter.h"
#include "FileReader.h"

namespace LibSWBF2::Types
{
	void LocalizeEntry::RefreshSize()
	{
		m_EntrySize = (uint8_t)(m_WideString.Size() * sizeof(uint16_t) + 6);
	}

	void LocalizeEntry::WriteToStream(FileWriter& stream)
	{
		stream.WriteUInt16(m_LocalizePathHash);
		stream.WriteUInt16(m_EntrySize);
		stream.WriteBytes((uint8_t*)m_WideString.GetArrayPtr(), m_WideString.Size() * sizeof(uint16_t));
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

		int i = numWideChars - 1;
		for (; i > 0; i -= 2)
		{
			if (m_WideString[i] != 0 || m_WideString[i - 1] != 0)
			{
				break;
			}
		}

		m_WideString.Resize((size_t)i + 1);
	}

	//String LocalizeEntry::ToString() const
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