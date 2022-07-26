#include "pch.h"
#include "BARR.h"

#include "XFRM.h"
#include "SIZE.h"

#include "Logging/Logger.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::wrld
{

    void BARR_FLAG::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void BARR_FLAG::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void BARR_FLAG::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);
		m_Flag = stream.ReadUInt32();
        BaseChunk::EnsureEnd(stream);
    }

    String BARR_FLAG::ToString() const
    {
    	return fmt::format("{0}", m_Flag).c_str();
    }




    void BARR_INFO::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void BARR_INFO::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void BARR_INFO::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

		while (ThereIsAnother(stream))
		{
            ChunkHeader next = stream.ReadChunkHeader(true);
            if (next == "NAME"_h)
            {
                READ_CHILD(stream, p_Name);
            }
            else if (next == "XFRM"_h)
            {
                READ_CHILD(stream, p_Transform);
            }
            else if (next == "SIZE"_h)
            {
                READ_CHILD(stream, p_Size);
            }
            else if (next == "FLAG"_h)
            {
                READ_CHILD(stream, p_Flag);
            }
            else 
            {
                READ_CHILD_GENERIC(stream);
            }
		}

        BaseChunk::EnsureEnd(stream);
    }


    String BARR_INFO::ToString() const
    {
        return p_Name -> ToString();
    }





    void BARR::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void BARR::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void BARR::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

		while (ThereIsAnother(stream))
		{
            ChunkHeader next = stream.ReadChunkHeader(true);
            if (next == "INFO"_h)
            {
                READ_CHILD(stream, p_Info);
            }
            else 
            {
                READ_CHILD_GENERIC(stream);
            }
		}

        BaseChunk::EnsureEnd(stream);
    }


    String BARR::ToString() const
    {
        return p_Info == nullptr ? "" : p_Info -> ToString();
    }
}