#include "stdafx.h"
#include "coll.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"


namespace LibSWBF2::Chunks::LVL::coll
{
	void coll::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void coll::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void coll::ReadFromStream(FileReader& stream)
	{       
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        READ_CHILD(stream, p_ChunkName);
        READ_CHILD(stream, p_NodeName);

        READ_CHILD(stream, p_Info);
        READ_CHILD(stream, p_Verts);

        READ_CHILD(stream, p_SpatialDataStructure);

        /*
        //TEST ALWAYS PASSES
        for (int i = 0; i < p_SpatialDataStructure -> m_Leaves.Size(); i++)
        {
        	List<uint16_t> &indexList = p_SpatialDataStructure -> m_Leaves[i] -> m_Indicies;
        	
        	for (int j = 0; j < indexList.Size(); j++)
        	{
        		List<Vector3> &verts = p_Verts -> m_Content;
        		
        		if (indexList[j] >= verts.Size())
        		{
        			LOG_WARN("INDEX OUT OF BOUNDS IN TREE LEAF");
        		}
        	}
        }
        */

		BaseChunk::EnsureEnd(stream);
	}

    Types::String coll::ToString() 
    {
        return p_SpatialDataStructure -> ToString() + " Name: " + 
        								p_ChunkName -> ToString() +
        								fmt::format(" Num verts: {}", p_Verts -> m_Verts.Size()).c_str();
    }
}
