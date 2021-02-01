#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/LVL/config/DATA.h"


#include "Types/List.h"


namespace LibSWBF2::Chunks::LVL::config
{
    struct LIBSWBF2_API SCOP : public GenericChunk<"SCOP"_m>
    {
	    void RefreshSize() override;
	    void WriteToStream(FileWriter& stream) override;
	    void ReadFromStream(FileReader& stream) override;
    };
}
