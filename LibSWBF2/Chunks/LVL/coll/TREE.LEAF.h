#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
//#include "TREE.h"


namespace LibSWBF2::Chunks::LVL::coll
{
    struct LIBSWBF2_API TREE_LEAF : public GenericChunk<"LEAF"_m>
    {

    friend struct TREE;
    friend struct coll;

    public:
	    void RefreshSize() override;
	    void WriteToStream(FileWriter& stream) override;
	    void ReadFromStream(FileReader& stream) override;

        Types::String ToString() override;

    private:
        uint32_t m_FlattenedTreeIndex;
        List<uint16_t> m_Indicies;
    };
}