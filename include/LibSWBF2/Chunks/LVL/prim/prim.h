#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Chunks/STR.h>
#include <LibSWBF2/Chunks/LVL/prim/prim.INFO.h>
#include <LibSWBF2/Chunks/LVL/prim/MASK.h>
#include <LibSWBF2/Chunks/LVL/prim/prim.DATA.h>
#include <LibSWBF2/Chunks/LVL/wrld/XFRM.h>


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
