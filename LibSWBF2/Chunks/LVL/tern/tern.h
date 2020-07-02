#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
#include "tern.INFO.h"
#include "PCHS.h"
#include "LTEX.h"
#include "DTEX.h"

namespace LibSWBF2::Chunks::LVL::terrain
{
	struct LIBSWBF2_API tern : public GenericChunk<"tern"_m>
	{
	public:
		STR<"NAME"_m>* p_Name;
		STR<"DTLX"_m>* p_DetailTexture;
		INFO* p_Info;
		LTEX* p_LayerTextures;
		DTEX* p_LayerDetailTextures;
		PCHS* p_Patches;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}