#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Chunks/STR.h>
#include <LibSWBF2/Chunks/LVL/coll/POSI.h>
#include <LibSWBF2/Chunks/LVL/coll/TREE.h>
#include <LibSWBF2/Chunks/LVL/prim/MASK.h>
#include <LibSWBF2/Chunks/LVL/coll/coll.INFO.h>


namespace LibSWBF2::Chunks::LVL::coll
{
    struct LIBSWBF2_API coll : public GenericChunk<"coll"_m>
    {
    public:
	    void RefreshSize() override;
	    void WriteToStream(FileWriter& stream) override;
	    void ReadFromStream(FileReader& stream) override;

        Types::String ToString() const override;

        STR<"NAME"_m> *p_ChunkName;

        prim::MASK    *p_Mask;
        STR<"NODE"_m> *p_NodeName;

        INFO_coll *p_Info;
        TREE *p_Tree;
        POSI *p_Verts;
    };
}
