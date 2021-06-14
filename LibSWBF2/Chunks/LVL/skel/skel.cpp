#include "stdafx.h"
#include "skel.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::skel
{
    void skel::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void skel::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void skel::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        while (ThereIsAnother(stream))
        {
            ChunkHeader next = stream.ReadChunkHeader(true);
            if (next == "INFO"_h)
            {
                READ_CHILD(stream, p_Info);
            }
            else if (next == "NAME"_h)
            {
                READ_CHILD(stream, p_BoneNames);
            }
            else if (next == "PRNT"_h)
            {
                READ_CHILD(stream, p_BoneParents);
            }
            else if (next == "XFRM"_h)
            {
                READ_CHILD(stream, p_BoneTransforms);
            }
            else
            {
                READ_CHILD_GENERIC(stream);
            }
        }

        // NOTE: There is always exactly one less parent entry, since the
        // first Bone Name serves as root and therefore doesn't have a parent
        if (p_Info->m_BoneCount != p_BoneNames->m_Texts.Size() || 
            p_Info->m_BoneCount != (p_BoneParents->m_Texts.Size() + 1) || 
            p_Info->m_BoneCount != p_BoneTransforms->m_BoneRotations.Size() || 
            p_Info->m_BoneCount != p_BoneTransforms->m_BonePositions.Size())
        {
            LOG_WARN("Skeleton buffer sizes don't match up! Info Bone Count: {}, Bone Names: {}, Bone Parents (-1): {}, Bone Rotations: {}, Bone Positions: {} - Chunk Position: {}",
                p_Info->m_BoneCount,
                p_BoneNames->m_Texts.Size(),
                p_BoneParents->m_Texts.Size(),
                p_BoneTransforms->m_BoneRotations.Size(),
                p_BoneTransforms->m_BonePositions.Size(),
                GetPosition()
            );
        }

        BaseChunk::EnsureEnd(stream);
    }

    String skel::ToString() const
    {
        return p_Info != nullptr ? p_Info->ToString() : "INFO chunk missing!";
    }
}