#include "stdafx.h"
#include "tern.INFO.h"
#include "Exceptions.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::terrain
{
    void INFO::RefreshSize()
    {
        throw LibException("Not implemented!");
    }

    void INFO::WriteToStream(FileWriter& stream)
    {
        throw LibException("Not implemented!");
    }

    void INFO::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_GridUnitSize = stream.ReadFloat();
        m_HeightScale = stream.ReadFloat();
        m_HeightFloor = stream.ReadFloat();
        m_HeightCeiling = stream.ReadFloat();
        m_GridSize = stream.ReadUInt16();
        m_HeightPatches = stream.ReadUInt16();
        m_TexturePatches = stream.ReadUInt16();
        m_TextureCount = stream.ReadUInt16();
        m_MaxTextureLayers = stream.ReadUInt16();
        m_Unknown = stream.ReadUInt16();

        BaseChunk::EnsureEnd(stream);
    }
}