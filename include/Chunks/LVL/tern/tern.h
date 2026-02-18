#pragma once
#include <Chunks/GenericChunk.h>
#include <Chunks/STR.h>
#include <Chunks/LVL/tern/tern.INFO.h>
#include <Chunks/LVL/tern/PCHS.h>
#include <Chunks/LVL/tern/LTEX.h>
#include <Chunks/LVL/tern/DTEX.h>

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

		String ToString() const override;
	};
}