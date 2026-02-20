#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Chunks/STR.h>
#include <LibSWBF2/Types/List.h>
#include <LibSWBF2/Types/LibString.h>


namespace LibSWBF2::Chunks::LVL::coll
{
    struct LIBSWBF2_API POSI : public GenericChunk<"POSI"_m>
    {
    public:
	    void RefreshSize() override;
	    void WriteToStream(FileWriter& stream) override;
	    void ReadFromStream(FileReader& stream) override;

	    Types::String ToString() const override;

        List<Vector3> m_Verts;
    };
}