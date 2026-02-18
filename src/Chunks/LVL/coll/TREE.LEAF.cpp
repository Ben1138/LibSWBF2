#include <LibSWBF2/pch.h>
#include <LibSWBF2/Chunks/LVL/coll/TREE.LEAF.h>
#include "InternalHelpers.h"
#include <LibSWBF2/IO/FileReader.h>
#include <LibSWBF2/Types/Enums.h>
#include <LibSWBF2/Logging/Logger.h>
#include <string>


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

        uint32_t numIndicies = (uint32_t) stream.ReadByte();

        stream.SkipBytes(6); //unknown

        for (uint32_t i = 0; i < numIndicies; i++)
        {
        	m_Indicies.Add(stream.ReadUInt16());
        }

		BaseChunk::EnsureEnd(stream);
	}

	
    Types::String TREE_LEAF::ToString() const 
    {
        std::string stringRep = "{";

        for (int i = 0; i < m_Indicies.Size(); i++)
        {
        	stringRep += fmt::format(" {}", m_Indicies[i]).c_str();
        }

        stringRep += " }";
        return stringRep.c_str();
    }
}
