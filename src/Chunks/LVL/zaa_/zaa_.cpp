#include <LibSWBF2/pch.h>
#include <LibSWBF2/Chunks/LVL/zaa_/zaa_.h>
#include "InternalHelpers.h"
#include <LibSWBF2/IO/FileReader.h>
#include <LibSWBF2/Exceptions.h>

namespace LibSWBF2::Chunks::LVL::animation
{
	void zaa_::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void zaa_::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void zaa_::ReadFromStream(FileReader& stream)
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

			LOG_ERROR("{}", le.what());
			p_Bin = nullptr;
		}

		BaseChunk::EnsureEnd(stream);
	}

	String zaa_::ToString() const
	{
		return fmt::format(
			"Name: {}\n\n",
			p_Name->m_Text
		).c_str();
	}
}