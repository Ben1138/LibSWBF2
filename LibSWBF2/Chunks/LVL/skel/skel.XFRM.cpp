#include "stdafx.h"
#include "skel.XFRM.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "skel.h"

namespace LibSWBF2::Chunks::LVL::skel
{
    void XFRM::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void XFRM::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void XFRM::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        skel* parent = dynamic_cast<skel*>(GetParent());
        if (parent == nullptr)
        {
            THROW("Parent is NOT a skel chunk!");
        }

        m_BoneRotations.Clear();
        m_BonePositions.Clear();
        for (uint32_t i = 0; i < parent->p_Info->m_BoneCount; ++i)
        {
            m_BoneRotations.Emplace().ReadFromStream(stream);
            m_BonePositions.Emplace().ReadFromStream(stream);
        }

        if (m_BoneRotations.Size() != m_BonePositions.Size())
        {
            THROW("Number of Bone Rotations {} does not match up with number of Bone Positions {}!", m_BoneRotations.Size(), m_BonePositions.Size());
        }

        BaseChunk::EnsureEnd(stream);
    }

    String XFRM::ToString() const
    {
        if (m_BoneRotations.Size() != m_BonePositions.Size())
        {
            THROW("Number of Bone Rotations {} does not match up with number of Bone Positions {}!", m_BoneRotations.Size(), m_BonePositions.Size());
        }

        std::string result;
        for (size_t i = 0; i < m_BoneRotations.Size(); ++i)
        {
            result += fmt::format(
                "Rotation: \n{}\n"
                "Position: {}\n\n",
                m_BoneRotations[i].ToString(),
                m_BonePositions[i].ToString()
            );
        }
        return result.c_str();
    }
}