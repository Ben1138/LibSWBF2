#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/Enums.h"
#include "Types/TerrainBufferEntry.h"

namespace LibSWBF2::Chunks::LVL::terrain
{
	struct LIBSWBF2_API PTCH_INFO : public GenericChunk<"INFO"_m>
	{
	public:

		uint32_t m_ElementSize;
		List<uint32_t> m_TextureSlotsUsed;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}