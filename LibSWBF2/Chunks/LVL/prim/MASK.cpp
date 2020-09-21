#include "stdafx.h"
#include "MASK.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"



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

        m_MaskFlags = stream.ReadUInt32();

        BaseChunk::EnsureEnd(stream);
    }

    Types::String MASK::ToString()
    {
        String stringRep("[");

        if ((m_MaskFlags & 0x1) != 0)
        {
            stringRep = stringRep + " Ordnance";
        }

        if ((m_MaskFlags & 0x2) != 0)
        {
            stringRep = stringRep + " Vehicle";
        }

        if ((m_MaskFlags & 0x4) != 0)
        {
            stringRep = stringRep + " Building";
        }

        if ((m_MaskFlags & 0x8) != 0)
        {
            stringRep = stringRep + " Terrain";
        }

        if ((m_MaskFlags & 0x10) != 0)
        {
            stringRep = stringRep + " Soldier";
        }

        if ((m_MaskFlags & 0x20) != 0)
        {
            stringRep = stringRep + " Flag";
        }

        return stringRep + " ]";
    }
}
