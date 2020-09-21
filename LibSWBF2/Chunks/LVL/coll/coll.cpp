#include "stdafx.h"
#include "coll.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"


namespace LibSWBF2::Chunks::LVL::coll
{
	void coll::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void coll::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void coll::ReadFromStream(FileReader& stream)
	{       
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        READ_CHILD(stream, p_ChunkName);
        READ_CHILD(stream, p_NodeName);

        READ_CHILD_GENERIC(stream);
        READ_CHILD(stream, p_Verts);

		BaseChunk::EnsureEnd(stream);
	}

    Types::String coll::ToString() 
    {
        return p_ChunkName -> ToString();
    }
}
