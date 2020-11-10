#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
#include "POSI.h"
#include "TREE.h"
#include "../prim/MASK.h"
#include "coll.INFO.h"


namespace LibSWBF2::Chunks::LVL::coll
{
    struct LIBSWBF2_API coll : public GenericChunk<"coll"_m>
    {
    public:
	    void RefreshSize() override;
	    void WriteToStream(FileWriter& stream) override;
	    void ReadFromStream(FileReader& stream) override;

        Types::String ToString() override;

        STR<"NAME"_m> *p_ChunkName;

        prim::MASK    *p_Mask;
        STR<"NODE"_m> *p_NodeName;

        INFO_coll *p_Info;
        TREE *p_Tree;
        POSI *p_Verts;
    };
}