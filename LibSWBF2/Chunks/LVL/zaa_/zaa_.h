#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
#include "BIN_.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	struct LIBSWBF2_API zaa_ : public GenericChunk<"zaa_"_m>
	{
	public:
		STR<"NAME"_m>* p_Name;
		BIN_* p_Bin;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}