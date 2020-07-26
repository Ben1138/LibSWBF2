#pragma once
#include "req.h"
#include "Chunks/BNK/BNK.h"
#include "Types/LibString.h"

namespace LibSWBF2::Wrappers
{
	using Types::List;
	using Types::String;
	using Chunks::GenericBaseChunk;
	using Chunks::BNK::BNK;

	/*
	 * This and the other wrapper classes just serve as abstraction Layers
	 * to wrap around the chunk data. You can of course just use the chunk data
	 * directly if you want. This is just to make access to desired data more
	 * straight forward.
	 */
	class LIBSWBF2_API SoundBank
	{
	private:
		SoundBank(BNK* soundBank);
		~SoundBank();

	private:
		BNK* p_soundBank;

	public:

		static SoundBank* FromFile(String path);
		static void Destroy(SoundBank* soundBank);

		uint32_t GetNumSoundClips() const;
		bool GetSoundClip(uint32_t index, FNVHash& nameHash, uint32_t& sampleRate, uint32_t& sampleCount, uint8_t& blockAlign, uint8_t*& data) const;
	};
}