#include "stdafx.h"
#include "Logging/Logger.h"
#include "DirectX/DXHelpers.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "DATA.h"


namespace LibSWBF2::Chunks::LVL::common
{
    void DATA::RefreshSize()
    {
        //THROW("Not implemented!");
        return;
    }

    void DATA::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void DATA::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
    }

	String DATA::ToString()
	{
	    return String("DATA");
	}
}
