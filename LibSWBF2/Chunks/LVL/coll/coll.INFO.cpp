#include "stdafx.h"
#include "coll.INFO.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"


namespace LibSWBF2::Chunks::LVL::coll
{
	void INFO_coll::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void INFO_coll::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void INFO_coll::ReadFromStream(FileReader& stream)
	{       
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        stream.SkipBytes(16);
        m_BBoxMin.ReadFromStream(stream);
        m_BBoxMax.ReadFromStream(stream);

		BaseChunk::EnsureEnd(stream);
	}

    Types::String INFO_coll::ToString() 
    {
        return "BBox lower: " + m_BBoxMin.ToString() + ", BBox upper: " + m_BBoxMax.ToString();
    }
}
