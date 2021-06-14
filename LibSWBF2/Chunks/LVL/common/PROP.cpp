#include "stdafx.h"
#include "PROP.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Hashing.h"

namespace LibSWBF2::Chunks::LVL::common
{
    void PROP::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void PROP::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void PROP::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_PropertyName = stream.ReadUInt32();
        m_Value = stream.ReadString();

        BaseChunk::EnsureEnd(stream);
    }

    String PROP::ToString() const
    {
        String name;
        if (!FNV::Lookup(m_PropertyName, name))
        {
            name = std::to_string(m_PropertyName).c_str();
        }

        return fmt::format(
            "Property Name: {}\n"
            "Value: {}",
            name,
            m_Value
        ).c_str();
    }
}