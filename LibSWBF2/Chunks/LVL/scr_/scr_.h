#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
#include "scr_.INFO.h"
#include "Chunks/RawData.h"

namespace LibSWBF2::Chunks::LVL::script
{
	struct LIBSWBF2_API scr_ : public GenericChunk<"scr_"_m>
	{
	public:
		STR<"NAME"_m>* p_Name;
		INFO* p_Info;

		// TODO: are there cases with multiple bodies?
		RawData<"BODY"_m>* p_Body;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}