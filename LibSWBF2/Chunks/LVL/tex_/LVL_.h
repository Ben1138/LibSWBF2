#pragma once
#include "Chunks\GenericChunk.h"
#include "LVL_.INFO.h"
#include "BODY.h"

namespace LibSWBF2::Chunks::LVL
{
	using INFO = LibSWBF2::Chunks::LVL::LVL_texture::INFO;

	struct LIBSWBF2_EXP LVL_ : public GenericChunk<"LVL_"_m>
	{
	public:
		INFO* p_Info = nullptr;
		BODY* p_Body = nullptr;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}