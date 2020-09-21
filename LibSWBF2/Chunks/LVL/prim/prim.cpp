#include "stdafx.h"
#include "prim.h"
#include "prim.DATA.h"
#include "../wrld/XFRM.h"
#include "MASK.h"

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

        DATA_PRIM *tempDATA;
        wrld::XFRM *tempXFRM;
        MASK *tempMASK;
        STR<"NODE"_m> *tempNODE;
        STR<"PRNT"_m> *tempPRNT;
        STR<"NAME"_m> *tempNAME;


        READ_CHILD(stream, p_InfoHeader);
        ChunkHeader nextHeader;

        while (ThereIsAnother(stream))
        {
        	nextHeader = stream.ReadChunkHeader(true);
        	
        	if (nextHeader == "DATA"_h)
    		{
    			READ_CHILD(stream, tempDATA);
    		}
    		else if (nextHeader == "NODE"_h)
    		{
        		READ_CHILD(stream, tempNODE);
        	}
    		else if (nextHeader == "PRNT"_h)
    		{
        		READ_CHILD(stream, tempPRNT);
        	}
        	else if (nextHeader == "MASK"_h)
        	{
        		READ_CHILD(stream, tempMASK);
			}
			else if (nextHeader == "XFRM"_h)
			{
        		READ_CHILD(stream, tempXFRM);
			}
			else if (nextHeader == "NAME"_h)
			{
        		READ_CHILD(stream, tempNAME);
			}
			else 
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
