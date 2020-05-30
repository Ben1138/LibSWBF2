#pragma once
#include "GenericChunk.h"
#include "D3D9Types.h"
#include "STR.h"
#include "tex_.INFO.h"
#include "FMT_.h"

namespace LibSWBF2::Chunks::LVL
{
	struct LIBSWBF2_EXP tex_ : public GenericChunk
	{
	public:
		STR* p_Name;
		texture::INFO* p_Info;
		List<FMT_*> m_FMTs;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}