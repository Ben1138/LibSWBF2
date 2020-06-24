#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
#include "tern.INFO.h"
#include "PCHS.h"

namespace LibSWBF2::Chunks::LVL
{
	struct LIBSWBF2_API tern : public GenericChunk<"tern"_m>
	{
	public:
		STR<"NAME"_m>* p_Name;
		terrain::INFO* p_Info;
		terrain::PCHS* p_Patches;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}