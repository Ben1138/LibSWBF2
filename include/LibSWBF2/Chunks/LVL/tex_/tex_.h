#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/DirectX/D3D9FORMAT.h>
#include <LibSWBF2/Chunks/STR.h>
#include <LibSWBF2/Chunks/LVL/tex_/tex_.INFO.h>
#include <LibSWBF2/Chunks/LVL/tex_/FMT_.h>

namespace LibSWBF2::Chunks::LVL::texture
{
	struct LIBSWBF2_API tex_ : public GenericChunk<"tex_"_m>
	{
	public:
		STR<"NAME"_m>* p_Name;
		texture::INFO* p_Info;
		List<FMT_*> m_FMTs;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}