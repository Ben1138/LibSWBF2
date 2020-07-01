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
        m_Scale = stream.ReadFloat();
        m_HeightFloor = stream.ReadFloat();
        m_HeightCeiling = stream.ReadFloat();
        m_GridSize = stream.ReadUInt16();
        m_PatchEdgeSize = stream.ReadUInt16();
        m_TexturePatches = stream.ReadUInt16();
        m_TextureCount = stream.ReadUInt16();
        m_MaxTextureLayers = stream.ReadUInt16();
        m_Unknown = stream.ReadUInt16();

        BaseChunk::EnsureEnd(stream);
    }

    String INFO::ToString()
    {
        return fmt::format(
            "Grid Unit Size: {}\n"
            "Scale: {}\n"
            "Height Floor: {}\n"
            "Height Ceiling: {}\n"
            "Grid Size: {}\n"
            "Patch Edge Size: {}\n"
            "Texture Patches: {}\n"
            "Texture Count: {}\n"
            "Max Texture Layers: {}\n"
            "Unknown: {}\n",
            m_GridUnitSize,
            m_Scale,
            m_HeightFloor,
            m_HeightCeiling,
            m_GridSize,
            m_PatchEdgeSize,
            m_TexturePatches,
            m_TextureCount,
            m_MaxTextureLayers,
            m_Unknown
        ).c_str();
    }
}