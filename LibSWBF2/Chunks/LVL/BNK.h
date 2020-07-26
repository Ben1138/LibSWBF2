#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/SoundBank.h"

namespace LibSWBF2::Chunks::LVL
{
	using Types::SoundBank;
	using Types::SoundClip;

	struct LIBSWBF2_API BNK : public GenericChunk<"ucfb"_m>
	{
		static BNK* Create();
		static void Destroy(BNK* soundBank);

		SoundBank m_SoundBank;

		void ReadFromStream(FileReader& stream) override;
		String ToString() override;

	protected:
		BNK() = default;
		~BNK() = default;
	};
}