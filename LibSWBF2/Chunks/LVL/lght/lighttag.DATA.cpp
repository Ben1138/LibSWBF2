#include "stdafx.h"
#include "lighttag.DATA.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"


namespace LibSWBF2::Chunks::LVL::lght
{

	void DATA_TAG::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void DATA_TAG::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void DATA_TAG::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
        Check(stream);

        uint32_t localFlag = stream.ReadUInt32();
        m_LocalLight = localFlag == 3801947695 ? true : false;

        if (m_LocalLight)
        {
        	stream.SkipBytes(9); //Not sure what those 9 bytes mean as of yet
        	m_Name = stream.ReadString((size_t) stream.ReadUInt32());
        }

        BaseChunk::EnsureEnd(stream);
	}
}
