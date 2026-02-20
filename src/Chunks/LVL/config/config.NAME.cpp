#include <LibSWBF2/pch.h>
#include <LibSWBF2/Chunks/LVL/config/config.NAME.h>
#include "InternalHelpers.h"
#include <LibSWBF2/IO/FileReader.h>
#include <LibSWBF2/Types/Enums.h>
#include <LibSWBF2/Logging/Logger.h>


namespace LibSWBF2::Chunks::LVL::config
{
	void config_NAME::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void config_NAME::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void config_NAME::ReadFromStream(FileReader& stream)
	{       
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_Name = stream.ReadUInt32();

		BaseChunk::EnsureEnd(stream);
	}

    String config_NAME::ToString() const 
    {
        return fmt::format("0x{0:x}", m_Name).c_str();
    }
}
