#include "stdafx.h"
#include "STRMULT.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks
{
    template<uint32_t Header>
    void STRMULT<Header>::RefreshSize()
    {
        THROW("Not implemented!");
    }

    template<uint32_t Header>
    void STRMULT<Header>::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    template<uint32_t Header>
    void STRMULT<Header>::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        GenericChunk<Header>::Check(stream);

        m_Texts.Clear();
        while (BaseChunk::PositionInChunk(stream.GetPosition()))
        {
            String next = stream.ReadString();
            if (!next.IsEmpty())
            {
                m_Texts.Add(next);
            }
        }

        BaseChunk::EnsureEnd(stream);
    }

    template<uint32_t Header>
    String STRMULT<Header>::ToString() const
    {
        std::string result;
        for (size_t i = 0; i < m_Texts.Size(); ++i)
        {
            result += m_Texts[i].Buffer() + std::string("\n");
        }
        return result.c_str();
    }
}

namespace LibSWBF2::Chunks
{
    template LIBSWBF2_API struct STRMULT<"NAME"_m>;
    template LIBSWBF2_API struct STRMULT<"PRNT"_m>;
    template LIBSWBF2_API struct STRMULT<"ANIM"_m>;
}