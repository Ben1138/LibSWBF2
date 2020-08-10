/*
Will contain class for the very generic DATA Chunk
*/
#include "stdafx.h"


#include "Chunks/GenericChunk.h"
#include "DATA.h"

namespace LibSWBF2::Chunks::LVL::common
{

struct SCOP : public GenericChunk<"SCOP"_m>{
		//void RefreshSize() override;
		//void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		//String ToString() override;
};

}