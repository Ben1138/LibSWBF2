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
            // also load when no specific sub LVLs have been specified at all
            if (root->m_SubLVLsToLoad.Size() == 0 || root->m_SubLVLsToLoad.Find(m_NameHash) >= 0)
            {
                ReadGenerics(stream);
            }
            else
            {
                SkipChunk(stream, false);

                String name;
                if (FNV::Lookup(m_NameHash, name))
                {
                    LOG_INFO("Skipping unspecified sub LVL '{}'", name);
                }
                else
                {
                    LOG_INFO("Skipping unspecified sub LVL, Hash: {}", m_NameHash);
                }
            }
        }

        BaseChunk::EnsureEnd(stream);
    }

    String lvl_::ToString()
    {
        String name;
        if (TryLookupName(name))
        {
            return fmt::format("Unhashed Name: {}", name).c_str();
        }
        return fmt::format("No table entry found for Hashed Name: {}", m_NameHash).c_str();
    }

    bool lvl_::TryLookupName(String& result)
    {
        return FNV::Lookup(m_NameHash, result);
    }
}