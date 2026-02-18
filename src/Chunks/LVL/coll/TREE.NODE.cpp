#include <LibSWBF2/pch.h>
#include <LibSWBF2/Chunks/LVL/coll/TREE.NODE.h>
#include "InternalHelpers.h"
#include <LibSWBF2/IO/FileReader.h>
#include <LibSWBF2/Types/Enums.h>
#include <LibSWBF2/Logging/Logger.h>


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

        m_VecLower.ReadFromStream(stream);
        m_VecUpper.ReadFromStream(stream);

		BaseChunk::EnsureEnd(stream);
	}

    Types::String TREE_NODE::ToString() const 
    {
        return fmt::format("Lower vector: {}\nHigher vector: {}",
        				    m_VecLower.ToString().Buffer(),
        				    m_VecUpper.ToString().Buffer()).c_str();
    }
}
