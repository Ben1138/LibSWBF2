#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/SoundClip.h"

namespace LibSWBF2::Chunks::LVL::sound
{
	using Types::SoundClip;

	struct LIBSWBF2_API emo_ : public GenericChunk<"emo_"_m>
	{
	public:
		uint32_t m_NumClips;
		List<SoundClip> m_Clips;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}