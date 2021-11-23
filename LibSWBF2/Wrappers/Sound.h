#pragma once
#include "Types/SoundClip.h"
#include "Types/LibString.h"
#include "Types/List.h"

namespace LibSWBF2::Wrappers
{
	using LibSWBF2::Types::SoundClip;
	using LibSWBF2::Types::String;
	using LibSWBF2::Types::List;

	class Level;
	class SoundBank;
	class SoundStream;

	// I'm doing this extra Sound wrapper calls just to 
	// follow the standardization..... Feels wrong though
	class LIBSWBF2_API Sound
	{
	private:
		friend Level;
		friend SoundBank;
		friend SoundStream;
		friend List<Sound>;

		Sound() = default;
		~Sound() = default;

	private:
		uint32_t m_NumChannels = 1;
		bool m_HasData;
		uint32_t m_FileOffset;
		uint8_t *m_DataPtr;
		SoundClip* p_SoundClip;

	public:
		static bool FromSoundClip(SoundClip* soundClip, Sound& out);

		bool HasData() const;

		String GetName() const;
		FNVHash GetHashedName() const;
		bool GetData(uint32_t& sampleRate, uint32_t& sampleCount, uint8_t& blockAlign, const uint8_t*& data) const;
	};
}