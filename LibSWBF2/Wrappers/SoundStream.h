#pragma once
#include "Types/SoundClip.h"
#include "InternalHelpers.h"
#include "Wrappers/Sound.h"
#include "Types/LibString.h"
#include "Types/List.h"




namespace LibSWBF2
{
	class Container;

	namespace Chunks::LVL::sound
	{
		struct Stream;
	}	
}



namespace LibSWBF2::Wrappers
{
	using LibSWBF2::Types::String;
	using LibSWBF2::Types::List;
	using LibSWBF2::Chunks::LVL::sound::Stream;

	class Level;
  

	class LIBSWBF2_API SoundStream
	{
	private:
		friend Level;
		friend List<SoundStream>;

		SoundStream() = default;
		~SoundStream() = default;

		Stream* p_StreamChunk;

		List<Sound> m_Sounds;

		class SoundMapsWrapper* m_NameToIndexMaps;


	public:
		static bool FromChunk(Stream* stream, SoundStream& out);

		FNVHash GetHashedName() const;

		uint32_t GetFormat() const;
		uint32_t GetNumChannels() const;

		bool HasSegment(FNVHash segmentName) const;

		const List<Sound>& GetSounds() const;
		const Sound* GetSound(const String& soundName) const;
		const Sound* GetSound(FNVHash soundHash) const;

	};
}