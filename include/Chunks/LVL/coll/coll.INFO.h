#pragma once
#include "Chunks/GenericChunk.h"


namespace LibSWBF2::Chunks::LVL::coll
{
    struct LIBSWBF2_API INFO_coll : public GenericChunk<"INFO"_m>
    {
    public:
	    void RefreshSize() override;
	    void WriteToStream(FileWriter& stream) override;
	    void ReadFromStream(FileReader& stream) override;

        Types::String ToString() const override;

        Vector3 m_BBoxMin, m_BBoxMax;
        uint32_t m_NumVerts, m_NumInternalNodes, m_NumLeafNodes, m_NumIndiciesInTree;
    };
}