#include <LibSWBF2/pch.h>
#include <LibSWBF2/Chunks/LVL/skel/skel.INFO.h>
#include "InternalHelpers.h"
#include <LibSWBF2/IO/FileReader.h>

namespace LibSWBF2::Chunks::LVL::skel
{
    void INFO::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void INFO::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void INFO::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_ModelName = stream.ReadString();
        m_BoneCount = stream.ReadUInt32();

        BaseChunk::EnsureEnd(stream);
    }

    String INFO::ToString() const
    {
        return fmt::format(
            "Model Name: {}\n"
            "Bone Count: {}\n",
            m_ModelName,
            m_BoneCount
        ).c_str();
    }
}