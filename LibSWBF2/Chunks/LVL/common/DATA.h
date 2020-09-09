#pragma once

#include "stdafx.h"
#include "Chunks/GenericChunk.h"
#include "Chunks/RawData.h"
#include "Types/Enums.h"
#include "FileReader.h"



namespace LibSWBF2::Chunks::LVL::common
{

struct LIBSWBF2_API DATA : public GenericChunk<"DATA"_m> {

	static uint32_t PeekDATATag(FileReader& stream)
	{
		stream.SkipBytes(8);
		uint32_t result = stream.ReadUInt32();
		stream.SetPosition(stream.GetPosition() - 12);
		return result;
	}

};

}
