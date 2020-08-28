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

        m_LocalLight = stream.ReadUInt32() == 3801947695;

        if (m_LocalLight)
        {
        	stream.SkipBytes(9); //Not sure what those 9 bytes mean as of yet
        	m_Name = stream.ReadString((size_t) stream.ReadUInt32());
        }

        BaseChunk::EnsureEnd(stream);
	}

	String DATA_TAG::ToString()
	{
		if (!m_LocalLight)
		{
			return "Global lighting section";
		}
		else 
		{
			return m_Name.Buffer();
		}
	}
}
