#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/SoundClip.h"

namespace LibSWBF2::Chunks::BNK
{
	using Types::SoundClip;

	// Munged sound bank files.
	// These do not contain any sub chunks!
	struct LIBSWBF2_API BNK : public GenericChunk<"ucfb"_m>
	{
		static BNK* Create();
		static void Destroy(BNK* soundBank);

		FNVHash m_NameHash;
		uint32_t m_NumClips;

		// size of all samples from all clips
		uint32_t m_DataSize;

		List<SoundClip> m_Clips;

		void ReadFromStream(FileReader& stream) override;
		String ToString() override;

	protected:
		BNK() = default;
		~BNK() = default;
	};
}