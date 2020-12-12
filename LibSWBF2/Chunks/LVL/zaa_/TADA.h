#pragma once
#include "Chunks/GenericChunk.h"

namespace LibSWBF2::Chunks::LVL::animation
{

	/*
	TADA (ADAT == animation data?)

	This chunk is a bit strange.  I haven't gotten it 100% figured out like 
	TNJA, but this implementation should be able to read 90% of animations properly.


	*/

	struct LIBSWBF2_API TADA : public GenericChunk<"TADA"_m>
	{

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;

		~TADA();

		uint8_t *p_DataBuffer = nullptr;
		size_t m_DataBufferLength = 0;
	};
}