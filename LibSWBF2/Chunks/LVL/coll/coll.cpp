#include "pch.h"
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

        prim::MASK *tempMASK = nullptr;
        if (stream.ReadChunkHeader(true) == "MASK"_h)
        {
            READ_CHILD(stream, tempMASK);
        }

        p_Mask = tempMASK;

        READ_CHILD(stream, p_NodeName);
        READ_CHILD(stream, p_Info);
        READ_CHILD(stream, p_Verts);
        READ_CHILD(stream, p_Tree);

		BaseChunk::EnsureEnd(stream);
	}

    Types::String coll::ToString() const
    {
        return p_Tree -> ToString()  +
               " Name: " + p_ChunkName -> ToString() +
        		fmt::format(" Num verts: {}", p_Verts -> m_Verts.Size()).c_str();
    }
}
