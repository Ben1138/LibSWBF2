#include "pch.h"
#include "TREE.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"


namespace LibSWBF2::Chunks::LVL::coll
{
	void TREE::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void TREE::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void TREE::ReadFromStream(FileReader& stream)
	{       
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        TREE_NODE *tempNode;
        TREE_LEAF *tempLeaf;

        ChunkHeader nextHeader;

        int index = 0;

        while(ThereIsAnother(stream))
        {
        	nextHeader = stream.ReadChunkHeader(true);

        	if (nextHeader == "NODE"_h)
        	{
        		READ_CHILD(stream,tempNode);
        		tempNode -> m_FlattenedTreeIndex = index++;
        		m_Nodes.Add(tempNode);
        	}
        	else if (nextHeader == "LEAF"_h)
        	{
        		READ_CHILD(stream, tempLeaf)
        		tempLeaf -> m_FlattenedTreeIndex = index++;
        		m_Leaves.Add(tempLeaf);
        	}
        	else
        	{
                LOG_WARN("Irregular TREE child: {}", nextHeader.ToString());
        		READ_CHILD_GENERIC(stream);
        	}
        }

		BaseChunk::EnsureEnd(stream);
	}

    Types::String TREE::ToString() const 
    {
        return fmt::format("{} internal nodes, {} leaf nodes",
        				    m_Nodes.Size(),
        				    m_Leaves.Size()).c_str();
    }
}
