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
                READ_CHILD(stream, tempScope);
     
                p_localLightHeaders.Add(tempHeader);
                p_localLightBlocks.Add(tempScope);
                
                //This in combo with PositionInChunk might be a bad way...
                ForwardToNextHeader(stream);
            }

            /*
            COUT(fmt::format("Number of lights: {}", 
                            p_localLightHeaders.Size()));
            COUT(fmt::format("First light block has {} fields", 
                            p_localLightBlocks[0] -> p_dataFields.Size()));
            */

            lght::skip = true;
        }
        else
        {
            //Skip second one
            //COUT("SKIPPING lght CHUNK");
        }

        //COUT("END lght CHUNK");
        
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
