#pragma once
#include "Types/SoundClip.h"
#include "InternalHelpers.h"
#include "Wrappers/Sound.h"
#include "Audio/SoundDecoder.h"
//#include "Audio/AudioStreamer.h"
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
		~SoundStream();


		Stream* p_StreamChunk;

		List<Sound> m_Sounds;

		/*
		File stream reader and buffer fields
		*/

		FileReader * p_Reader = nullptr;
		uint8_t * p_StreamBuffer = nullptr;
		size_t m_SizeStreamBuffer;

		/*
		Fields relating stream/buffer to current segment properties
		*/

		Sound * p_CurrentSegment = nullptr;
		size_t m_StreamBufferReadOffset;
		size_t m_StreamBufferDataSize;
		size_t m_SegmentOffset;

		/*
		Decoder, there was originally one for each substream,
		but soundmunge exe says substream interleave will never interrupt a
		IMAADPCM block, so one will do. 
		*/

		SoundDecoder * p_Decoder = nullptr;

		class SoundMapsWrapper* p_NameToIndexMaps;



	public:

		// Caller must provide stream (any subclass of FileReader) and pre-allocate/provide...
		bool SetFileReader(FileReader * reader);

		// the stream buffer and...
		bool SetFileStreamBuffer(uint8_t * buffer, size_t numBytes);

		// identify the specific segment to be read before calling...
		bool SetSegment(FNVHash segmentNameHash);

		// ReadBytesFromStream, which puts the encoded bytes in the stream buffer, after which
		// the final call to ReadSamples can proceed.
		int32_t ReadBytesFromStream(int32_t NumBytes);

		// Complicated, but I figured these params would need to be experimented with a lot
		// from C# so I wanted to keep all this exposed until we nail down exactly what 
		// buffering behavior is best in Unity.
		// Plus, we know from the Lua API that only one stream can be played from a given file
		// at any time, so it makes sense to give the option of sharing one stream and buffer
		// between multiple SoundStreams of the same file... 
        int32_t ReadSamples(void * samplesBuffer, size_t samplesBufferLength, 
        					size_t numSamplesToRead, ESoundFormat format);

		int32_t BytesLeftInSegment();

        /*
        // This method might not be needed, it depends on whether or not we
		// encounter other formats or if IMAADPCM block boundaries can be violated...
        int32_t ReadSamplesFromBytes(void * samplesBuffer, size_t samplesBufferLength, 
        							size_t numBytesToRead, ESoundFormat format, int32_t &bytesRead);
        */

        int32_t GetNumSamplesInBytes(int32_t NumBytes);



		static bool FromChunk(Stream* stream, SoundStream& out);


		FNVHash GetHashedName() const;

		ESoundFormat GetFormat() const;
		uint32_t GetNumChannels() const;

		uint32_t GetNumSubstreams() const;
		uint32_t GetSubstreamInterleave() const;
		uint32_t GetChannelInterleave() const;

		bool HasData() const;

		bool HasSegment(FNVHash segmentName) const;

		const List<Sound>& GetSounds() const;
		const Sound* GetSound(const String& soundName) const;
		const Sound* GetSound(FNVHash soundHash) const;
	};
}