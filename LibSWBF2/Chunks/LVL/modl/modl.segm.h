#pragma once
#include "Chunks\GenericChunk.h"
#include "Chunks\STR.h"
#include "segm.INFO.h"
#include "MTRL.h"

namespace LibSWBF2::Chunks::LVL::modl
{
	struct LIBSWBF2_EXP segm : public GenericChunk<"segm"_m>
	{
	public:
		segment::INFO* p_Info;
		MTRL* p_Material;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}