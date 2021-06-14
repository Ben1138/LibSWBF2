#include "stdafx.h"
#include "coll.INFO.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"

#include <string>


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

        m_NumVerts 		    = stream.ReadUInt32();
        m_NumInternalNodes  = stream.ReadUInt32();
        m_NumLeafNodes      = stream.ReadUInt32();
        m_NumIndiciesInTree = stream.ReadUInt32();
        
        m_BBoxMin.ReadFromStream(stream);
        m_BBoxMax.ReadFromStream(stream);

		BaseChunk::EnsureEnd(stream);
	}

    Types::String INFO_coll::ToString() const 
    {
    	return fmt::format("BBox lower: {}\nBBox upper: {}\nNum vertices in POSI: {}\nNum internal nodes {}\nNum leaf nodes: {}\nTotal num indicies in leaves: {}",
    		   m_BBoxMin.ToString().Buffer(), m_BBoxMax.ToString().Buffer(),
    		   m_NumVerts, m_NumInternalNodes, m_NumLeafNodes, 
    		   m_NumIndiciesInTree).c_str();
    }
}
