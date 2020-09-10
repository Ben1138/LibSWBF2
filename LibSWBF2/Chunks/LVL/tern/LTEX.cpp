#include "stdafx.h"
#include "LTEX.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "tern.h"

namespace LibSWBF2::Chunks::LVL::terrain
{
    void LTEX::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void LTEX::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void LTEX::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        tern* parent = dynamic_cast<tern*>(GetParent());
        if (parent == nullptr)
        {
            LOG_ERROR("Parent of LTEX is not a tern chunk!");
            return;
        }

        INFO* info = parent->p_Info;
        if (info == nullptr)
        {
            LOG_ERROR("Cannot read texture layers, terrain has no Info chunk!");
            return;
        }

        m_LayerTextures.Clear();
        for (uint16_t i = 0; i < info->m_TextureCount; ++i)
        {
            m_LayerTextures.Add(stream.ReadString());
        }

        BaseChunk::EnsureEnd(stream);
    }

    String LTEX::ToString()
    {
        std::string result;
        for (size_t i = 0; i < m_LayerTextures.Size(); ++i)
        {
            result += fmt::format("Layer {}: {}\n", i, m_LayerTextures[i]);
        }
        return result.c_str();
    }
}