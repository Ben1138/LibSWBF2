#include "stdafx.h"
#include "prim.h"
#include "prim.DATA.h"
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

        DATA_PRIM *tmpData;
        //STR<"NODE"> *tempNode;

        while (ThereIsAnother(stream))
        {
        	ChunkHeader nextHeader = stream.ReadChunkHeader(true);

        	if (nextHeader == "DATA"_h)
        	{
        		READ_CHILD(stream, tmpData);
        	} else if (nextHeader == "coll"_h)
        	{
        		stream.SetPosition(stream.GetPosition() + 1);
        		BaseChunk::ForwardToNextHeader(stream);
        	} else
        	{
		        READ_CHILD_GENERIC(stream);		
        	}       	
        }

		BaseChunk::EnsureEnd(stream);
	}


	Types::String prim::ToString()
	{
		return p_InfoHeader -> ToString();
	}
}
