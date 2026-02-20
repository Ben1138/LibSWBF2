#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Chunks/STR.h>
#include <LibSWBF2/Chunks/LVL/wrld/XFRM.h>
#include <LibSWBF2/Types/Enums.h>


namespace LibSWBF2::Chunks::LVL::prim
{
    struct LIBSWBF2_API MASK : public GenericChunk<"MASK"_m>
    {
    public:
	    void RefreshSize() override;
	    void WriteToStream(FileWriter& stream) override;
	    void ReadFromStream(FileReader& stream) override;

        Types::String ToString() const override;
        
        ECollisionMaskFlags m_MaskFlags; //solider, Ordnance, building, vehicle, etc...
    };
}
