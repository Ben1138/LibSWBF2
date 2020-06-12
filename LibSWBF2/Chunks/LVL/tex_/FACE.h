#pragma once
#include "Chunks\GenericChunk.h"
#include "tex_.LVL_.h"

namespace LibSWBF2::Chunks::LVL::texture
{
	using LVL_texture::LVL_;

	struct LIBSWBF2_EXP FACE : public GenericChunk<"FACE"_m>
	{
	public:
		List<LVL_*> m_LVLs;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}