#include <LibSWBF2/pch.h>
#include <LibSWBF2/Chunks/LVL/zaf_/zaf_.h>
#include <LibSWBF2/Chunks/LVL/zaf_/BIN_.h>
#include "InternalHelpers.h"
#include <LibSWBF2/IO/FileReader.h>
#include <LibSWBF2/Exceptions.h>

namespace LibSWBF2::Chunks::LVL::animation
{
	void zaf_::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void zaf_::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void zaf_::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		READ_CHILD(stream, p_Name);

		try 
		{
			READ_CHILD(stream, p_Bin);
		}
		catch (LibException le)
		{
			LOG_ERROR("{0}", le.what());
			p_Bin = nullptr;
		}

		BaseChunk::EnsureEnd(stream);
	}

	String zaf_::ToString() const
	{
		return fmt::format(
			"Animation skeleton of name: {}\n\n",
			p_Name->m_Text
		).c_str();
	}
}
