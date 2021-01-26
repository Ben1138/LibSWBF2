#pragma once
#include "Chunks/GenericChunk.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	struct LIBSWBF2_API MINA : public GenericChunk<"MINA"_m> //ANIM
	{
	public:

		List<uint32_t> m_TransBitFlags;
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