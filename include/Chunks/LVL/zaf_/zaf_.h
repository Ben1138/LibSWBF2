#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	struct ZAF_BIN_;

	struct LIBSWBF2_API zaf_ : public GenericChunk<"zaf_"_m>
	{
	public:
		STR<"NAME"_m>* p_Name;
		ZAF_BIN_* p_Bin;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}