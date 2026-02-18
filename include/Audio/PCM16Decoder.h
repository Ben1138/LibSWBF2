#pragma once

#include "Types/List.h"
#include "Logging/Logger.h"
#include "Wrappers/Sound.h"
#include "Audio/SoundDecoder.h"


/*
DecodeAndFillPCM16 is just a memcpy
*/


namespace LibSWBF2
{
	class PCM16Decoder : public SoundDecoder
	{
		public:

			PCM16Decoder();

			void Reset();

			int32_t DecodeAndFillPCM16(void * source, uint32_t maxBytes, int16_t * sampleSink, size_t numSamplesToExtract, size_t& bytesReadOut);
			int32_t DecodeAndFillUnity(void * source, uint32_t maxBytes, float * sampleSink, size_t numSamplesToExtract, size_t& bytesReadOut);
	
			size_t BytesNeededForSamples(size_t numSamples);

			size_t SamplesInBytes(size_t numBytes);
	};
}
