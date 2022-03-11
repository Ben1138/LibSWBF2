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

	/*
	class LIBSWBF2_API SoundStreamReader
	{
		friend SoundStream;
		
		FileReader * p_Reader = nullptr;

		uint8_t * p_StreamBuffer = nullptr;
		size_t m_SizeStreamBuffer;

		size_t m_StreamBufferReadOffset;
		size_t m_NumBytesInStreamBuffer;

		size_t m_SegmentOffset;

		SoundDecoder * p_Decoder;

		bool m_IsSubstream;
		size_t m_InterleaveSize;
		Sound * p_CurrentSegment = nullptr;

		int32_t BytesLeftInSegment();

	public: 

		~SoundStreamReader()
		{
			delete p_StreamBuffer;
			delete p_Decoder;
		}

		SoundStreamReader() = delete;
		SoundStreamReader(const SoundStreamReader&) = delete;

		SoundStreamReader(const SoundStream& str, const FileReader * reader, 
						size_t streamBufferSize, int32_t SubStreamIndex=-1)
		{
			p_StreamBuffer = new uint8_t[streamBufferSize];

			if (str.GetNumSubstreams() > 1)
			{

			}
		}

		bool SetSegment(FNVHash segmentNameHash);
        int32_t ReadSamples(void * samplesBuffer, size_t numSamplesToRead, ESoundFormat format);
        int32_t GetNumSamplesInBytes(int32_t NumBytes);

        int32_t Buffer(int32_t NumBytesToBuffer = -1)
        {

        }
	}
	*/


	class LIBSWBF2_API SoundStream
	{
	private:
		friend Level;
		//friend AudioStreamer;
		friend List<SoundStream>;

		SoundStream() = default;

		Stream* p_StreamChunk;

		List<Sound> m_Sounds;


		FileReader * p_Reader = nullptr;

		uint8_t * p_StreamBuffer = nullptr;
		size_t m_SizeStreamBuffer;

		size_t m_StreamBufferReadOffset;
		size_t m_StreamBufferDataSize;

		size_t m_SegmentOffset;


		uint8_t m_SubstreamIndex = 0;
		List<SoundDecoder *> m_Decoders;

		Sound * p_CurrentSegment = nullptr;


		class SoundMapsWrapper* p_NameToIndexMaps;



	public:

		bool SetFileReader(FileReader * reader);

		bool SetFileStreamBuffer(uint8_t * buffer, size_t numBytes);

		int32_t ReadBytesFromStream(int32_t NumBytes);

		int32_t BytesLeftInSegment();

		bool SetSegment(FNVHash segmentNameHash);

        int32_t ReadSamples(void * samplesBuffer, size_t samplesBufferLength, 
        					size_t numSamplesToRead, ESoundFormat format);

        int32_t ReadSamplesFromBytes(void * samplesBuffer, size_t samplesBufferLength, 
        							size_t numBytesToRead, ESoundFormat format, int32_t &bytesRead);

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