#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Types/Enums.h>
#include <LibSWBF2/Types/TerrainBufferEntry.h>

namespace LibSWBF2::Chunks::LVL::terrain
{
	struct LIBSWBF2_API IBUF : public GenericChunk<"IBUF"_m>
	{
	public:
		uint32_t m_ElementCount;
		List<uint16_t> m_IndexBuffer;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}