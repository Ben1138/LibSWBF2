#include "stdafx.h"
#include "lght.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"


namespace LibSWBF2::Chunks::LVL::lght
{
	void lght::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void lght::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}


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
            READ_CHILD(stream, p_Marker); //Will determine meaning when investigating other lght chunks...

            while (ThereIsAnother(stream))
            {
                DATA_TAG *tempHeader;
                SCOP_LGHT *tempScope;
                
                READ_CHILD(stream, tempHeader);

                if (DATA_TAG -> m_Local){
                    READ_CHILD(stream, tempScope);
                    p_LightTags.Add(tempHeader);
                    p_LightBodies.Add(tempScope);
                    m_NumLights++;
                }
                else 
                {
                    break;
                }
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
