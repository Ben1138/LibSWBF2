#pragma once
#include "LibString.h"
#include "List.h"

namespace LibSWBF2
{
	class FileReader;
	class FileWriter;
}

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API LocalizeEntry
	{
		FNVHash m_LocalizePathHash;		// hashed path, e.g. "common.quit2windows"
		uint16_t m_EntrySize;			// complete size of this entry
		List<uint16_t> m_WideString;	// TODO: Maybe introduce a "WideString" type?

		void RefreshSize();
		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		//String ToString() const;
	};
}