#include "stdafx.h"
#include "Locl.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::Localization
{
	void Locl::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void Locl::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void Locl::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		// order of these two chunks seems to be fixed.
		// so no need for dynamic chunk checking.
		READ_CHILD(stream, p_Name);
		READ_CHILD(stream, p_Body);

		BaseChunk::EnsureEnd(stream);
	}

	String Locl::ToString()
	{
		return fmt::format(
			"Language: {}\n"
			"Number of entries: {}",
			p_Name->m_Text,
			(uint32_t)p_Body->m_LocalizeEntries.Size()
		).c_str();
	}
}