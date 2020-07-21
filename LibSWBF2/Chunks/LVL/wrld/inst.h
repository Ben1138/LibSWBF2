#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
#include "inst.INFO.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
	struct LIBSWBF2_API inst : public GenericChunk<"inst"_m>
	{
	public:
		instance::INFO* p_Info;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}