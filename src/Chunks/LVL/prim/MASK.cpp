#include <LibSWBF2/pch.h>
#include <LibSWBF2/Chunks/LVL/prim/MASK.h>
#include "InternalHelpers.h"
#include <LibSWBF2/IO/FileReader.h>
#include <LibSWBF2/Types/Enums.h>
#include <LibSWBF2/Logging/Logger.h>



namespace LibSWBF2::Chunks::LVL::prim
{
    void MASK::RefreshSize()
    {
    	THROW("Not implemented!");
    }

    void MASK::WriteToStream(FileWriter& stream)
    {
    	THROW("Not implemented!");
    }

    void MASK::ReadFromStream(FileReader& stream)
    {       
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_MaskFlags = (ECollisionMaskFlags) stream.ReadUInt32();

        BaseChunk::EnsureEnd(stream);
    }

    Types::String MASK::ToString() const
    {
        return CollisionMaskTypeToString(m_MaskFlags);
    }
}
