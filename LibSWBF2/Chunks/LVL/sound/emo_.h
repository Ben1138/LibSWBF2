#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/SoundBank.h"

namespace LibSWBF2::Chunks::LVL::sound
{
	using Types::SoundBank;
	using Types::SoundClip;

	struct LIBSWBF2_API emo_ : public GenericChunk<"emo_"_m>
	{
	public:
		SoundBank m_SoundBank;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}