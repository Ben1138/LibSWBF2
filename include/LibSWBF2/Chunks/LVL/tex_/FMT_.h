#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Chunks/LVL/tex_/FMT_.INFO.h>
#include <LibSWBF2/Chunks/LVL/tex_/FACE.h>

namespace LibSWBF2::Chunks::LVL::texture
{
	struct LIBSWBF2_API FMT_ : public GenericChunk<"FMT_"_m>
	{
	public:
		FMT::INFO* p_Info = nullptr;

		// TODO: can there be multiple faces?
		FACE* p_Face = nullptr;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}