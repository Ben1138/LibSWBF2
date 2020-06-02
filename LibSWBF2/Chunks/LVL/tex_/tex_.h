#pragma once
#include "Chunks\GenericChunk.h"
#include "D3D9Types.h"
#include "Chunks\STR.h"
#include "tex_.INFO.h"
#include "FMT_.h"

namespace LibSWBF2::Chunks::LVL
{
	struct LIBSWBF2_EXP tex_ : public GenericChunk<"tex_"_m>
	{
	public:
		STR<"NAME"_m>* p_Name;
		texture::INFO* p_Info;
		List<FMT_*> m_FMTs;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}