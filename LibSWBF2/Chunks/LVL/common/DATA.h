#pragma once

#include "stdafx.h"
#include "Chunks/GenericChunk.h"
#include "Chunks/RawData.h"
#include "Types/Enums.h"


namespace LibSWBF2::Chunks::LVL::common
{

struct LIBSWBF2_API DATA : public RawData<"DATA"_m> {

	/*
	void RefreshSize() override;
	void WriteToStream(FileWriter& stream) override;
	void ReadFromStream(FileReader& stream) override;

	String ToString() override;
	*/
};

}
