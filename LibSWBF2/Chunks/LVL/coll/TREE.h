#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"

#include "TREE.NODE.h"
#include "TREE.LEAF.h"


namespace LibSWBF2::Chunks::LVL::coll
{
    struct LIBSWBF2_API TREE : public GenericChunk<"TREE"_m>
    {
    public:
	    void RefreshSize() override;
	    void WriteToStream(FileWriter& stream) override;
	    void ReadFromStream(FileReader& stream) override;

        Types::String ToString() override;

        List<TREE_NODE *> m_Nodes;
        List<TREE_LEAF *> m_Leaves;
    };
}