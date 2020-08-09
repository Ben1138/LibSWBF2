/*
Will contain class for the very generic DATA Chunk
*/

#include "Chunks/GenericChunk.h"
#include "DATA.h"

namespace LibSWBF2::Chunks::LVL::common
{

struct SCOP : public GenericChunk<"SCOP"_m>{
    void ReadFromStream(FileReader& stream) override;
};

}
