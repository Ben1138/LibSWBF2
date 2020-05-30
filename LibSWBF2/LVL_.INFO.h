#pragma once
#include "GenericChunk.h"

namespace LibSWBF2::Chunks::LVL::LVL_texture
{
	struct LIBSWBF2_EXP INFO : public GenericChunk
	{
	public:
		uint32_t m_MipLevel;
		uint32_t m_BodySize; // why did they put that here...

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}