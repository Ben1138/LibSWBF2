#include "stdafx.h"
#include "prim.INFO.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"


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

        m_StringMember  = stream.ReadString();
        m_NumPrimitives = stream.ReadUInt16();

		BaseChunk::EnsureEnd(stream);
	}

    Types::String INFO_prim::ToString() 
    {
    	return fmt::format("String member: {}\nNum primitives {}",
    		   m_StringMember.Buffer(), m_NumPrimitives).c_str();
    }
}
