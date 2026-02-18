#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Chunks/STR.h>

namespace LibSWBF2::Chunks::LVL::modl
{
	// Index Buffer
	struct LIBSWBF2_API IBUF : public GenericChunk<"IBUF"_m>
	{
	public:
		uint32_t m_IndicesCount;
		List<uint16_t> m_Indices;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}