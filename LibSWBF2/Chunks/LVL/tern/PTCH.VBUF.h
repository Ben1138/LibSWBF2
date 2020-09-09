#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/Enums.h"
#include "Types/TerrainBufferEntry.h"

namespace LibSWBF2::Chunks::LVL::terrain
{
	struct LIBSWBF2_API VBUF : public GenericChunk<"VBUF"_m>
	{
	public:
		uint32_t m_ElementCount;
		uint32_t m_ElementSize;
		ETerrainBufferType m_BufferType;
		List<Types::TerrainBufferEntry> m_TerrainBuffer;

		uint8_t *p_SplatMapData;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}