#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Types/Enums.h>
#include <LibSWBF2/Types/TerrainBufferEntry.h>

namespace LibSWBF2::Chunks::LVL::terrain
{
	struct LIBSWBF2_API PTCH_INFO : public GenericChunk<"INFO"_m>
	{
	public:

		List<uint32_t> m_TextureSlotsUsed;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}