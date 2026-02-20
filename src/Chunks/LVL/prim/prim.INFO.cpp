#include <LibSWBF2/pch.h>
#include <LibSWBF2/Chunks/LVL/prim/prim.INFO.h>
#include "InternalHelpers.h"
#include <LibSWBF2/IO/FileReader.h>
#include <LibSWBF2/Types/Enums.h>
#include <LibSWBF2/Logging/Logger.h>


namespace LibSWBF2::Chunks::LVL::prim
{
	void INFO_prim::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void INFO_prim::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void INFO_prim::ReadFromStream(FileReader& stream)
	{       
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_ModelName  = stream.ReadString();
        m_NumPrimitives = stream.ReadUInt16();

		BaseChunk::EnsureEnd(stream);
	}

    Types::String INFO_prim::ToString() const 
    {
    	return fmt::format("String member: {}\nNum primitives {}",
    		   m_ModelName.Buffer(), m_NumPrimitives).c_str();
    }
}
