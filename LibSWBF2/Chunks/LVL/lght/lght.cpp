#include "stdafx.h"
#include "lght.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"

#include <iostream>
#define COUT(x) std::cout << x << std::endl


namespace LibSWBF2::Chunks::LVL::light
{
	void lght::RefreshSize()
	{
		//THROW("Not implemented!");
        return;
	}

	void lght::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

    /*
     There isn't much abstraction here, just basic exposure
     of the chunk structure.  All light semantics are parsed from
     the SCOP/DATA chunks in the Light wrapper classes.
     */

	void lght::ReadFromStream(FileReader& stream)
	{
        
        COUT("READING lght CHUNK at: ");
        COUT(stream.GetPosition());
        
        BaseChunk::ReadFromStream(stream);
        Check(stream);
        
        /*
         There are 2 lght chunks in every lvl I've tested,
         I haven't looked into the second one yet since it
         doesn't have many readable strings, so skipping it
         for now...
         */
        
        if (!lght::skip)
        {
            READ_CHILD(stream, p_Marker);

            //PositionInChunk might not be best for this
            while (BaseChunk::PositionInChunk(stream.GetPosition()))
            {
                DATA *tempHeader;
                SCOP *tempScope;
                
                READ_CHILD(stream, tempHeader);
                COUT("header name: ");
                COUT((tempHeader -> GetHeader()).ToString().Buffer());

                READ_CHILD(stream, tempScope);
    
                LOG_WARN("FOUND A LIGHT");
                
                p_localLightHeaders.Add(tempHeader);
                p_localLightBlocks.Add(tempScope);
                
                //This in combo with PositionInChunk might be bad way...
                ForwardToNextHeader(stream);
            }
            
            lght::skip = true;
        }
        else
        {
            COUT("SKIPPING lght CHUNK");
        }
        
		BaseChunk::EnsureEnd(stream);
	}

	String lght::ToString()
	{
		return fmt::format(
			"Number of lights: {}",
			p_localLightHeaders.Size()
		).c_str();
	}
}
