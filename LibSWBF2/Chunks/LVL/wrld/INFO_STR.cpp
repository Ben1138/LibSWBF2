#include "stdafx.h"
#include "INFO_STR.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
    void anim_INFO::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void anim_INFO::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void anim_INFO::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_Name = stream.ReadString();

        BaseChunk::EnsureEnd(stream);
    }

    String anim_INFO::ToString()
    {
        return fmt::format("Name: {0}", m_Name.Buffer()).c_str();
    }
}