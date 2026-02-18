#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Types/Enums.h>
#include <LibSWBF2/Types/TerrainBufferEntry.h>

namespace LibSWBF2::Chunks::LVL::terrain
{
	struct LIBSWBF2_API VBUF : public GenericChunk<"VBUF"_m>
	{
	public:
		uint32_t m_ElementCount;
		uint32_t m_ElementSize;
		ETerrainBufferType m_BufferType;
		List<Types::TerrainBufferEntry> m_TerrainBuffer;

		List<uint8_t> m_BlendMapData;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}