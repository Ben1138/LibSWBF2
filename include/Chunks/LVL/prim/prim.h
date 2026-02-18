#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
#include "prim.INFO.h"
#include "MASK.h"
#include "prim.DATA.h"
#include "../wrld/XFRM.h"


namespace LibSWBF2::Chunks::LVL::prim
{
    struct LIBSWBF2_API prim : public GenericChunk<"prim"_m>
    {
	    void RefreshSize() override;
	    void WriteToStream(FileWriter& stream) override;
	    void ReadFromStream(FileReader& stream) override;

        Types::String ToString() const override;
        
        INFO_prim *p_InfoChunk;  
        
        List<STR<"NAME"_m> *> m_PrimitiveNAMEs;
        List<MASK *>          m_PrimitiveMASKs;
        List<STR<"PRNT"_m> *> m_PrimitivePRNTs;  
        List<wrld::XFRM *>    m_PrimitiveXFRMs;
        List<DATA_PRIM *>     m_PrimitiveDATAs;
    };
}