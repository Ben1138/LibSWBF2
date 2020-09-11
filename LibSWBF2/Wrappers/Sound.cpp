#include "stdafx.h"
#include "Sound.h"
#include "InternalHelpers.h"

namespace LibSWBF2::Wrappers
{
	bool Sound::FromSoundClip(SoundClip* soundClip, Sound& out)
	{
		if (soundClip == nullptr)
		{
			LOG_ERROR("Given soundClip was NULL!");
			return false;
		}

		out.p_SoundClip = soundClip;

		return true;
	}

	String Sound::GetName() const
	{
		String name;
		if (!p_SoundClip->TryLookupName(name))
		{
			name = std::to_string(p_SoundClip->m_NameHash).c_str();
		}
		return name;
	}

	FNVHash Sound::GetHashedName() const
	{
		return p_SoundClip->m_NameHash;
	}

	bool Sound::GetData(uint32_t& sampleRate, uint32_t& sampleCount, uint8_t& blockAlign, const uint8_t*& data) const
	{
		if (p_SoundClip == nullptr)
		{
			LOG_ERROR("Encapsuled SoundClip is NULL!");
			return false;
		}

		sampleRate = p_SoundClip->m_SampleRate;
		sampleCount = p_SoundClip->m_SampleCount;
		blockAlign = p_SoundClip->GetBytesPerSample();
		data = p_SoundClip->GetSampleData();
		return data != nullptr;
	}
}