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
         It seems in every ucfb, the first lght chunk contains
         all local lights, and the other per-world lght's merely index
         into the first one.  So for now, before we do per-world stuff,
         we just parse this first chunk.
         */

        if (!lght::skip)
        {
            STR<"NAME"_m> *p_Marker;
            READ_CHILD(stream, p_Marker);
            delete p_Marker;

            //PositionInChunk might not be best for this
            while (BaseChunk::PositionInChunk(stream.GetPosition()))
            {
                DATA *tempHeader;
                SCOP *tempScope;
                
                READ_CHILD(stream, tempHeader);
                READ_CHILD(stream, tempScope);

                //This in combo with PositionInChunk might be a bad way...
                ForwardToNextHeader(stream);
            }

            lght::skip = true;
        }
        else
        {
        	m_Empty = true;
        }
        
		BaseChunk::EnsureEnd(stream);
	}
}
