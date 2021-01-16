#include "stdafx.h"
#include "config.NAME.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"


namespace LibSWBF2::Chunks::LVL::lght
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

        m_WorldName = stream.ReadUInt32();

		BaseChunk::EnsureEnd(stream);
	}

    String config_NAME::ToString() 
    {
        return fmt::format("Hashed world name: 0x{0:x}", m_WorldName).c_str();
    }
}
