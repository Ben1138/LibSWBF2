#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"

namespace LibSWBF2::Chunks::LVL::animation
{

	/*
	TADA (ADAT == animation data?)

	Contains compressed animation data for each component of each
	rotation and location of each bone in each animation.

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