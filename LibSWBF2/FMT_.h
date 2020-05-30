#pragma once
#include "GenericChunk.h"
#include "FMT_.INFO.h"
#include "FACE.h"

namespace LibSWBF2::Chunks::LVL
{
	struct LIBSWBF2_EXP FMT_ : public GenericChunk
	{
	public:
		FMT::INFO* p_Info = nullptr;
		FACE* p_Face = nullptr;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}