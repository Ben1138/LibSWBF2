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

        READ_CHILD(stream, p_Marker); //Will determine meaning when investigating other lght chunks

        while (ThereIsAnother(stream))
        {
            DATA_TAG *tempTag;
            SCOP_LGHT *tempBody;
            
            READ_CHILD(stream, tempTag);

            if (tempTag -> m_LocalLight) //Check local flag before proceding
            {
                READ_CHILD(stream, tempBody);
                p_LightTags.Add(tempTag);
                p_LightBodies.Add(tempBody);
            }
            else 
            {
                READ_CHILD_GENERIC(stream);
            }
        }

		BaseChunk::EnsureEnd(stream);
	}
}
