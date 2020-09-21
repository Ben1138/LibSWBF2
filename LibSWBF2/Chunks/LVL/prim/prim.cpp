#include "stdafx.h"
#include "prim.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"



namespace LibSWBF2::Chunks::LVL::prim
{
	void prim::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void prim::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void prim::ReadFromStream(FileReader& stream)
	{       
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        READ_CHILD(stream, p_InfoHeader);

        //while (ThereIsAnother(stream))
        //{
	    //    READ_CHILD_GENERIC(stream);
	        //READ_CHILD_GENERIC(stream);
	        //READ_CHILD_GENERIC(stream);

	        //READ_CHILD(stream, p_Transform);

	        //READ_CHILD_GENERIC(stream);        	
        //}

		BaseChunk::EnsureEnd(stream);
	}


	Types::String prim::ToString()
	{
		return p_InfoHeader -> ToString();
	}
}
