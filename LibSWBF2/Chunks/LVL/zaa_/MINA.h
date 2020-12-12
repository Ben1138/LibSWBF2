#pragma once
#include "Chunks/GenericChunk.h"

namespace LibSWBF2::Chunks::LVL::animation
{

	/*
	ANIM lists each animation with their hashes, and numbers of bones/frames.
	ANIM chunk contains two subchunks, TNJA and TADA.
	*/

	struct LIBSWBF2_API MINA : public GenericChunk<"MINA"_m> //ANIM
	{
	public:

		List<uint32_t> m_AnimNameHashes;
		List<uint16_t> m_AnimFrameCounts;
		List<uint16_t> m_AnimBoneCounts;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}