#include "stdafx.h"
#include "SoundBank.h"
#include "InternalHelpers.h"
#include "Types/SoundClip.h"
#include "Hashing.h"
#include <unordered_map>

namespace LibSWBF2::Wrappers
{
	using Types::SoundClip;


	SoundBank::SoundBank(BNK* soundBank)
	{
		p_soundBank = soundBank;
		m_NameToIndexMaps = new SoundMapsWrapper();

		List<SoundClip>& clips = soundBank->m_SoundBank.m_Clips;
		for (size_t i = 0; i < clips.Size(); ++i)
		{
			Sound sound;
			if (Sound::FromSoundClip(&clips[i], sound))
			{
				size_t index = m_Sounds.Add(sound);
				m_NameToIndexMaps->SoundHashToIndex.emplace(clips[i].m_NameHash, index);
			}
		}
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
		delete m_NameToIndexMaps;
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

	SoundBank* SoundBank::FromChunk(BNK* soundChunk)
	{
		if (soundChunk == nullptr)
		{
			LOG_WARN("Given soundCHunk is NULL!");
			return nullptr;
		}
		return new SoundBank(soundChunk);
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

	const List<Sound>& SoundBank::GetSounds() const
	{
		return m_Sounds;
	}

	const Sound* SoundBank::GetSound(String soundName) const
	{
		if (soundName.IsEmpty())
		{
			return nullptr;
		}

		return GetSound(FNV::Hash(soundName));
	}

	const Sound* SoundBank::GetSound(FNVHash soundHash) const
	{
		auto it = m_NameToIndexMaps->SoundHashToIndex.find(soundHash);
		if (it != m_NameToIndexMaps->SoundHashToIndex.end())
		{
			return &m_Sounds[it->second];
		}

		//LOG_WARN("Could not find Sound '{}'!", soundHash);
		return nullptr;
	}
}