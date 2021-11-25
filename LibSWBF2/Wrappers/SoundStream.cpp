#include "pch.h"
#include "SoundStream.h"
#include "Chunks/LVL/sound/Stream.h"
#include "Chunks/LVL/sound/StreamInfo.h"

#include "InternalHelpers.h"
#include "Types/SoundClip.h"
#include "Hashing.h"
#include <unordered_map>
#include <iostream>

namespace LibSWBF2::Wrappers
{
	using Types::SoundClip;


	bool SoundStream::FromChunk(Stream* streamChunk, SoundStream& out)
	{
		if (streamChunk == nullptr)
		{
			LOG_ERROR("Given Stream chunk was NULL!");
			return false;
		}

		out.p_StreamChunk = streamChunk;
		out.m_NameToIndexMaps = new SoundMapsWrapper();

		List<SoundClip>& clips = streamChunk -> p_Info -> m_SoundHeaders;
		for (size_t i = 0; i < clips.Size(); ++i)
		{
			Sound sound;
			if (Sound::FromSoundClip(&clips[i], sound))
			{
				sound.m_Format = streamChunk -> p_Info -> m_Format;
				sound.m_NumChannels = streamChunk -> p_Info -> m_NumChannels;
				size_t index = out.m_Sounds.Add(sound);
				out.m_NameToIndexMaps->SoundHashToIndex.emplace(clips[i].m_NameHash, index);
			}
		}

		return true;
	}


	FNVHash SoundStream::GetHashedName() const
	{
		return p_StreamChunk -> p_Info -> m_Name;
	}

	ESoundFormat SoundStream::GetFormat() const
	{
		return p_StreamChunk -> p_Info -> m_Format;
	}

	uint32_t SoundStream::GetNumChannels() const
	{
		return p_StreamChunk -> p_Info -> m_NumChannels;
	}


	bool SoundStream::HasSegment(FNVHash segmentName) const
	{
		auto it = m_NameToIndexMaps->SoundHashToIndex.find(segmentName);
		return it == m_NameToIndexMaps->SoundHashToIndex.end();
	}


	bool SoundStream::HasData() const
	{
		return p_StreamChunk -> p_Data != nullptr;
	}



	const List<Sound>& SoundStream::GetSounds() const
	{
		return m_Sounds;
	}

	const Sound* SoundStream::GetSound(const String& soundName) const
	{
		if (soundName.IsEmpty())
		{
			return nullptr;
		}

		return GetSound(FNV::Hash(soundName));
	}

	const Sound* SoundStream::GetSound(FNVHash soundHash) const
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