#include "pch.h"
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
            LOG_WARN("Could not find outermost LVL root parent?!");
        }
        else
        {
            m_LVLType = root->m_LVLType;

            // also load when no specific sub LVLs have been specified at all
            if (root->m_SubLVLsToLoad.Size() == 0 || root->m_SubLVLsToLoad.Contains(m_NameHash))
            {
                ReadContents(stream);
            }
            else
            {
                LOG_INFO("Skipping unspecified sub LVL '{}'", m_NameHash);
                SkipChunk(stream, false);
            }
        }

        BaseChunk::EnsureEnd(stream);
    }

    void lvl_::ReadContents(FileReader& stream)
    {
        // for sound LVLs, there's a regular Sound Bank Header section before
        // other chunks (snd_) are following
        /*
        if (m_LVLType == ELVLType::Sound)
        {
            m_SoundBankHeader.ReadFromStream(stream);
        }
        else
        {
            // this else can be removed once we enable sound lvl_
            // ReadGeneric down below
            ReadGenerics(stream);
        }
        */

        // there are snd_ child chunks, but further down the
        // hierarchy there will be emo_ chunks who don't follow the spec
        // of header (emo_) followed by chunk size (uint32)...
        // ignore children fow now to not pollute the log with warnings
        ReadGenerics(stream);
    }

    String lvl_::ToString() const
    {
        String name;
        if (!FNV::Lookup(m_NameHash, name))
            name = std::to_string(m_NameHash).c_str();

        std::string result = fmt::format(
            "Name: {}\n"
            "LVL Type: {}\n",
            name,
            LVLTypeToString(m_LVLType)
        );

        if (m_LVLType == ELVLType::Sound)
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