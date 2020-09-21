#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
//#include "TREE.h"


namespace LibSWBF2::Chunks::LVL::coll
{
    struct LIBSWBF2_API TREE_NODE : public GenericChunk<"NODE"_m>
    {

    friend struct TREE;

    public:
	    void RefreshSize() override;
	    void WriteToStream(FileWriter& stream) override;
	    void ReadFromStream(FileReader& stream) override;

        Types::String ToString() override;

        Vector3u8 m_VecLower, m_VecUpper;

    private:
        uint32_t m_FlattenedTreeIndex;
    };
}