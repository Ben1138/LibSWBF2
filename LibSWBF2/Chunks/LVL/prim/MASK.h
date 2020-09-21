#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
#include "../wrld/XFRM.h"
#include "Types/Enums.h"


namespace LibSWBF2::Chunks::LVL::prim
{
    struct LIBSWBF2_API MASK : public GenericChunk<"MASK"_m>
    {
    public:
	    void RefreshSize() override;
	    void WriteToStream(FileWriter& stream) override;
	    void ReadFromStream(FileReader& stream) override;

        Types::String ToString() override;
        
        ECollisionMaskFlags m_MaskFlags; //solider, Ordnance, building, vehicle, etc...
    };
}