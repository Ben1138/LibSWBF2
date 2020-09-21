#include "stdafx.h"
#include "TREE.LEAF.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"


namespace LibSWBF2::Chunks::LVL::coll
{
	void TREE_LEAF::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void TREE_LEAF::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void TREE_LEAF::ReadFromStream(FileReader& stream)
	{       
        BaseChunk::ReadFromStream(stream);
        Check(stream);
		BaseChunk::EnsureEnd(stream);
	}

	/*
    Types::String TREE_LEAF::ToString() 
    {
        return p_ChunkName -> ToString();
    }
    */
}
