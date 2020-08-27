#pragma once

/*
Will contain class for the very generic DATA Chunk
*/
#include "stdafx.h"


#include "Chunks/GenericChunk.h"
#include "Chunks/LVL/common/DATA.h"
#include "Types/List.h"


namespace LibSWBF2::Chunks::LVL::lght
{

struct LIBSWBF2_API SCOP_LGHT : public GenericChunk<"SCOP"_m>{
	
	void RefreshSize() override;
	void WriteToStream(FileWriter& stream) override;
	void ReadFromStream(FileReader& stream) override;

	String ToString() override;

	List<DATA *> p_DataFields; 
};

}