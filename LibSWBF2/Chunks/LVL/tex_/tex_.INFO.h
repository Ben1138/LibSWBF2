#pragma once
#include "Chunks/GenericChunk.h"
#include "DirectX/D3D9FORMAT.h"

namespace LibSWBF2::Chunks::LVL::texture
{
	struct LIBSWBF2_API INFO : public GenericChunk<"INFO"_m>
	{
		uint32_t m_FormatCount;
		List<D3DFORMAT> m_Formats;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}