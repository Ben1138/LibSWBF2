#include "pch.h"
#include "SoundBank.h"
#include "Chunks/LVL/sound/SampleBank.h"
#include "Chunks/LVL/sound/SampleBankInfo.h"

#include "InternalHelpers.h"
#include "Types/SoundClip.h"
#include "Hashing.h"
#include <unordered_map>

namespace LibSWBF2::Wrappers
{
	using Types::SoundClip;


	bool SoundBank::FromChunk(SampleBank* bankChunk, SoundBank& out)
	{
		if (bankChunk == nullptr)
		{
			LOG_WARN("Given SampleBank chunk is NULL!");
			return false;
		}

		out.p_soundBank = bankChunk;
		out.m_NameToIndexMaps = new SoundMapsWrapper();

		List<SoundClip>& clips = bankChunk -> p_Info -> m_SoundHeaders;
		for (size_t i = 0; i < clips.Size(); ++i)
		{
			Sound sound;
			if (Sound::FromSoundClip(&clips[i], sound))
			{
				sound.m_Format = out.p_soundBank -> p_Info -> m_Format;
				sound.m_NumChannels = 1;
				size_t index = out.m_Sounds.Add(sound);
				out.m_NameToIndexMaps->SoundHashToIndex.emplace(clips[i].m_NameHash, index);
			}
		}

		return true;
	}


	const ESoundFormat SoundBank::GetFormat() const
	{
		return p_soundBank -> p_Info -> m_Format;	
	}

	const FNVHash SoundBank::GetHashedName() const
	{
		return p_soundBank -> p_Info -> m_Name;			
	}

	const bool SoundBank::HasData() const
	{
		return p_soundBank -> p_Data != nullptr;
	}


	const List<Sound>& SoundBank::GetSounds() const
	{
		return m_Sounds;
	}

	const Sound* SoundBank::GetSound(const String& soundName) const
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