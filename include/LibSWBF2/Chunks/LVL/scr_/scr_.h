#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Chunks/STR.h>
#include <LibSWBF2/Chunks/LVL/scr_/scr_.INFO.h>
#include <LibSWBF2/Chunks/RawData.h>

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

		String ToString() const override;
	};
}