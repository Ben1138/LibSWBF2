#pragma once
#include "Chunks\GenericChunk.h"
#include "D3D9Types.h"

namespace LibSWBF2::Chunks::LVL::FMT
{
	struct LIBSWBF2_API INFO : public GenericChunk<"INFO"_m>
	{
		D3DFORMAT m_Format;
		uint16_t m_Width;
		uint16_t m_Height;
		uint16_t m_Depth;
		uint16_t m_MipmapCount;
		uint32_t m_Type;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}