#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/RawData.h"

namespace LibSWBF2::Chunks::LVL::sound
{
	struct SampleBankInfo;

	struct LIBSWBF2_API SampleBank : public GenericChunk<"SampleBank"_fnv>
	{
		SampleBankInfo *p_Info;
		RawData<"Data"_fnv> *p_Data;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}