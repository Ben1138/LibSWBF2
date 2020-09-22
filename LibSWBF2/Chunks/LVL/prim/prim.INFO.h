#pragma once
#include "Chunks/GenericChunk.h"


namespace LibSWBF2::Chunks::LVL::prim
{
    struct LIBSWBF2_API INFO_prim : public GenericChunk<"INFO"_m>
    {
    public:
	    void RefreshSize() override;
	    void WriteToStream(FileWriter& stream) override;
	    void ReadFromStream(FileReader& stream) override;

        Types::String ToString() override;

        Types::String m_ModelName;
        uint16_t m_NumPrimitives;
    };
}