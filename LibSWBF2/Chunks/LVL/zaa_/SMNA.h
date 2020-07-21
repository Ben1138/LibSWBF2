#pragma once
#include "Chunks/GenericChunk.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	struct LIBSWBF2_API SMNA : public GenericChunk<"SMNA"_m>
	{
	public:
		uint32_t m_Unknown1;
		uint32_t m_Unknown2;
		uint32_t m_Unknown3;
		uint32_t m_NumAnimations;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}