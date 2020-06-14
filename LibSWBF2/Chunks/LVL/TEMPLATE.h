#pragma once
#include "Chunks\GenericChunk.h"
#include "Chunks\STR.h"

namespace LibSWBF2::Chunks::LVL
{
	struct LIBSWBF2_EXP segm : public GenericChunk<"segm"_m>
	{
	public:
		STR<"NAME"_m>* m_Name;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}