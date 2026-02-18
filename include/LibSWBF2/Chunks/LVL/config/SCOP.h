#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Chunks/LVL/config/DATA.h>


#include <LibSWBF2/Types/List.h>


namespace LibSWBF2::Chunks::LVL::config
{
    struct LIBSWBF2_API SCOP : public GenericChunk<"SCOP"_m>
    {
	    void RefreshSize() override;
	    void WriteToStream(FileWriter& stream) override;
	    void ReadFromStream(FileReader& stream) override;
    };
}
