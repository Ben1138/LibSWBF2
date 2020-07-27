#include "stdafx.h"
#include "lvl_.h"
#include "LVL.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Hashing.h"

namespace LibSWBF2::Chunks::LVL
{
    void lvl_::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void lvl_::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void lvl_::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_NameHash = stream.ReadUInt32();
        m_SizeLeft = stream.ReadUInt32();

        // Special case sub LVL: When LVL::ReadFromFile with optional specified
        // sub LVLs is called, only load the sub LVL if it has been specified there.
        // For that, we first need to go up the parentship hierarchy to find the root LVL chunk
        GenericBaseChunk* next = this;
        GenericBaseChunk* last = nullptr;
        do
        {
            last = next;
            next = next->GetParent();
        } while (next != nullptr);

        LVL* root = dynamic_cast<LVL*>(last);
        if (root == nullptr)
        {
            LOG_ERROR("Could not find outermost LVL root parent?!");
        }
        else
        {
            m_IsSoundLVL = root->m_IsSoundLVL;

            String name;
            if (!TryLookupName(name))
            {
                name = fmt::format("Hash: {}", m_NameHash).c_str();
            }

            // also load when no specific sub LVLs have been specified at all
            if (root->m_SubLVLsToLoad.Size() == 0 || root->m_SubLVLsToLoad.Contains(m_NameHash))
            {
                ReadContents(stream);
            }
            else
            {
                LOG_INFO("Skipping unspecified sub LVL '{}'", name);
                SkipChunk(stream, false);
            }
        }

        BaseChunk::EnsureEnd(stream);
    }

    void lvl_::ReadContents(FileReader& stream)
    {
        // for sound LVLs, there's a regular Sound Bank Header section before
        // other chunks (snd_) are following
        if (m_IsSoundLVL)
        {
            m_SoundBankHeader.ReadFromStream(stream);
        }

        ReadGenerics(stream);
    }

    String lvl_::ToString()
    {
        String name;
        if (!FNV::Lookup(m_NameHash, name))
            name = std::to_string(m_NameHash).c_str();

        std::string result = fmt::format(
            "Name: {}\n"
            "Is Sound LVL: {}\n",
            name,
            m_IsSoundLVL ? "Yes" : "No"
        );

        if (m_IsSoundLVL)
        {
            result += "\n" + std::string(m_SoundBankHeader.ToString().Buffer());
        }

        return result.c_str();
    }

    bool lvl_::TryLookupName(String& result)
    {
        return FNV::Lookup(m_NameHash, result);
    }
}