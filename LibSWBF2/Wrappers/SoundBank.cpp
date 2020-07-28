#include "stdafx.h"
#include "SoundBank.h"
#include "InternalHelpers.h"
#include "Types/SoundClip.h"
#include "Hashing.h"
#include <unordered_map>

namespace LibSWBF2::Wrappers
{
	using Types::SoundClip;

	class SoundMapsWrapper
	{
	public:
		std::unordered_map<std::string, size_t> SoundNameToIndex;
		std::unordered_map<FNVHash, size_t> SoundHashToIndex;
	};


	SoundBank::SoundBank(BNK* soundBank)
	{
		p_soundBank = soundBank;
		m_NameToIndexMaps = new SoundMapsWrapper();
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

		List<SoundClip>& clips = soundBank->m_SoundBank.m_Clips;
		for (size_t i = 0; i < clips.Size(); ++i)
		{
			Sound sound;
			if (Sound::FromSoundClip(&clips[i], sound))
			{
				size_t index = result->m_Sounds.Add(sound);

				String name;
				if (clips[i].TryLookupName(name))
				{
					result->m_NameToIndexMaps->SoundNameToIndex.emplace(ToLower(name), index);
				}
				else
				{
					result->m_NameToIndexMaps->SoundHashToIndex.emplace(clips[i].m_NameHash, index);
				}
			}
		}

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

		auto it = m_NameToIndexMaps->SoundNameToIndex.find(ToLower(soundName));
		if (it != m_NameToIndexMaps->SoundNameToIndex.end())
		{
			return &m_Sounds[it->second];
		}

		//LOG_WARN("Could not find Sound '{}'!", soundName);
		return nullptr;
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