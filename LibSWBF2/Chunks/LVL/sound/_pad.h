#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"

namespace LibSWBF2::Chunks::LVL::sound
{
	struct LIBSWBF2_API _pad : public GenericChunk<"_pad"_m>
	{
	public:
		uint32_t m_Unknown1;
		uint32_t m_SizeNextStreamChunk;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}