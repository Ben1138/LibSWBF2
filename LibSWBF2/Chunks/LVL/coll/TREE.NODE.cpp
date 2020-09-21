#include "stdafx.h"
#include "TREE.NODE.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"


namespace LibSWBF2::Chunks::LVL::coll
{
	void TREE_NODE::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void TREE_NODE::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void TREE_NODE::ReadFromStream(FileReader& stream)
	{       
        BaseChunk::ReadFromStream(stream);
        Check(stream);
		BaseChunk::EnsureEnd(stream);
	}

	/*
    Types::String TREE_NODE::ToString() 
    {
        return p_ChunkName -> ToString();
    }
    */
}
