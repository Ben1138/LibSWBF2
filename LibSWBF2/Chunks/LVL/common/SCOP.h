#pragma once

/*
Will contain class for the very generic DATA Chunk
*/
#include "stdafx.h"


#include "Chunks/GenericChunk.h"
#include "DATA.h"
#include "Types/List.h"

namespace LibSWBF2::Chunks::LVL::common
{

struct LIBSWBF2_API SCOP : public GenericChunk<"SCOP"_m>{
	
	void RefreshSize() override;
	void WriteToStream(FileWriter& stream) override;
	void ReadFromStream(FileReader& stream) override;

	String ToString() override;

	List<DATA *> p_dataFields; 
};

}