#include "stdafx.h"
#include "SoundBank.h"
#include "InternalHelpers.h"
#include "Types/SoundClip.h"

namespace LibSWBF2::Wrappers
{
	using Types::SoundClip;

	SoundBank::SoundBank(BNK* soundBank)
	{
		p_soundBank = soundBank;
	}

	SoundBank::~SoundBank()
	{
		if (p_soundBank == nullptr)
		{
			LOG_ERROR("p_soundBank of SoundBank was NULL!");
		}
		else
		{
			BNK::Destroy(p_soundBank);
		}
	}

	SoundBank* SoundBank::FromFile(String path)
	{
		BNK* soundBank = BNK::Create();
		if (!soundBank->ReadFromFile(path))
		{
			BNK::Destroy(soundBank);
			return nullptr;
		}
		
		SoundBank* result = new SoundBank(soundBank);
		return result;
	}

	void SoundBank::Destroy(SoundBank* SoundBank)
	{
		if (SoundBank == nullptr)
		{
			LOG_ERROR("Given SoundBank was NULL!");
			return;
		}

		delete SoundBank;
	}

	uint32_t SoundBank::GetNumSoundClips() const
	{
		return (uint32_t)p_soundBank->m_Clips.Size();
	}

	bool SoundBank::GetSoundClip(uint32_t index, FNVHash& nameHash, uint32_t& sampleRate, uint32_t& sampleCount, uint8_t& blockAlign, const uint8_t*& data) const
	{
		if (index >= p_soundBank->m_Clips.Size())
		{
			LOG_ERROR("Sound clip index {} is out of range ({})", index, p_soundBank->m_Clips.Size());
			return false;
		}

		SoundClip& clip = p_soundBank->m_Clips[index];
		nameHash = clip.m_NameHash;
		sampleRate = clip.m_SampleRate;
		sampleCount = clip.m_SampleCount;
		blockAlign = clip.GetBytesPerSample();
		data = clip.GetSampleData();
		return true;
	}
}