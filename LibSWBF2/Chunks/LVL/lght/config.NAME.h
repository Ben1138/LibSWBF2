#pragma once
#include "Chunks/GenericChunk.h"
#include "Hashing.h"


namespace LibSWBF2::Chunks::LVL::lght
{
    struct LIBSWBF2_API config_NAME : public GenericChunk<"NAME"_m>
    {
    public:
	    void RefreshSize() override;
	    void WriteToStream(FileWriter& stream) override;
	    void ReadFromStream(FileReader& stream) override;

        FNVHash m_WorldName;

        String ToString() override;
    };
}