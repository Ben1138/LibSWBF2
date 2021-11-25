#pragma once
#include "req.h"
#include "Types/LibString.h"
#include "Types/Enums.h"
#include "Sound.h"





namespace LibSWBF2
{
	class Container;

	namespace Chunks::LVL::sound
	{
		struct SampleBank;
	}	
}

namespace LibSWBF2::Wrappers
{
	using Types::List;
	using Types::String;
	using LibSWBF2::Chunks::LVL::sound::SampleBank;


	class LIBSWBF2_API SoundBank
	{
	private:
		friend Level;
		friend List<SoundBank>;

		SoundBank() = default;
		~SoundBank() = default;

	private:
		SampleBank* p_soundBank;
		List<Sound> m_Sounds;
		class SoundMapsWrapper* m_NameToIndexMaps;

	public:

		static bool FromChunk(SampleBank* stream, SoundBank& out);

		const bool HasData() const;

		const List<Sound>& GetSounds() const;
		const Sound* GetSound(const String& soundName) const;
		const Sound* GetSound(FNVHash soundHash) const;

		const ESoundFormat GetFormat() const;
		const FNVHash GetHashedName() const;
	};
}
