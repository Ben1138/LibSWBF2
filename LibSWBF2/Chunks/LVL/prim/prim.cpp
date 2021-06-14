#include "stdafx.h"
#include "prim.h"

#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"



namespace LibSWBF2::Chunks::LVL::prim
{
	void prim::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void prim::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void prim::ReadFromStream(FileReader& stream)
	{       
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        DATA_PRIM *tempDATA;
        wrld::XFRM *tempXFRM;
        MASK *tempMASK;
        STR<"PRNT"_m> *tempPRNT;
        STR<"NAME"_m> *tempNAME;

        READ_CHILD(stream, p_InfoChunk);
        ChunkHeader nextHeader;

        for (int i = 0; i < p_InfoChunk -> m_NumPrimitives; i++)
        {
            READ_CHILD(stream, tempNAME);
            m_PrimitiveNAMEs.Add(tempNAME);

            tempMASK = nullptr;
            if (stream.ReadChunkHeader(true) == "MASK"_h)
            {
                READ_CHILD(stream, tempMASK);
            }

            m_PrimitiveMASKs.Add(tempMASK);

            READ_CHILD(stream, tempPRNT);
            m_PrimitivePRNTs.Add(tempPRNT);

            READ_CHILD(stream, tempXFRM);
            m_PrimitiveXFRMs.Add(tempXFRM);

            READ_CHILD(stream, tempDATA);
            m_PrimitiveDATAs.Add(tempDATA);     	
        }

		BaseChunk::EnsureEnd(stream);
	}


	Types::String prim::ToString() const
	{
		return p_InfoChunk -> ToString();
	}
}
