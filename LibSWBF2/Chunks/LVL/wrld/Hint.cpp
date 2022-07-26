#include "pch.h"
#include "Hint.h"

#include "XFRM.h"

#include "Logging/Logger.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::wrld
{

    void Hint_TYPE::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void Hint_TYPE::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void Hint_TYPE::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);
		m_Type = stream.ReadUInt16();
        BaseChunk::EnsureEnd(stream);
    }

    String Hint_TYPE::ToString() const
    {
    	return fmt::format("{0}", m_Type).c_str();
    }




    void Hint_INFO::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void Hint_INFO::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void Hint_INFO::ReadFromStream(FileReader& stream)
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
            else if (next == "TYPE"_h)
            {
                READ_CHILD(stream, p_Type);
            }
            else 
            {
                READ_CHILD_GENERIC(stream);
            }
		}

        BaseChunk::EnsureEnd(stream);
    }


    String Hint_INFO::ToString() const
    {
        return p_Name -> ToString();
    }





    void Hint::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void Hint::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void Hint::ReadFromStream(FileReader& stream)
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
            else if (next == "PROP"_h)
            {
                READ_CHILD(stream, m_Properties.Emplace());
            }
            else 
            {
                READ_CHILD_GENERIC(stream);
            }
		}

        BaseChunk::EnsureEnd(stream);
    }


    String Hint::ToString() const
    {
        return p_Info == nullptr ? "" : p_Info -> ToString();
    }
}