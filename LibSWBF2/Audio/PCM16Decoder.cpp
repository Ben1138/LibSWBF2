#include "Types/List.h"
#include "Logging/Logger.h"
#include "PCM16Decoder.h"

#include <iostream>

namespace LibSWBF2
{
	PCM16Decoder::PCM16Decoder()
	{
	}

	void PCM16Decoder::Reset()
	{
	}


	size_t PCM16Decoder::BytesNeededForSamples(size_t numSamples)
	{
		return numSamples * 2;
	}

	size_t PCM16Decoder::SamplesInBytes(size_t numBytes)
	{
		return numBytes / 2;
	}

	int32_t PCM16Decoder::DecodeAndFillPCM16(void * source, uint32_t maxBytes, int16_t * sampleSink, size_t numSamplesToExtract, size_t& bytesReadOut)
	{
		auto bytesNeeded = BytesNeededForSamples(numSamplesToExtract);
		uint32_t NumBytesToCopy = bytesNeeded > maxBytes ? maxBytes : bytesNeeded;

		memcpy((void *) sampleSink, source, NumBytesToCopy);

		bytesReadOut = NumBytesToCopy;

		return NumBytesToCopy / 2;
	}




	int32_t PCM16Decoder::DecodeAndFillUnity(void * source, uint32_t maxBytes, float * sampleSink, size_t numSamplesToExtract, size_t& bytesReadOut)
	{
		auto bytesNeeded = BytesNeededForSamples(numSamplesToExtract);
		uint32_t NumBytesToRead = bytesNeeded > maxBytes ? maxBytes : bytesNeeded;

		float mult = 1 / 32768.0f;

		int sampleIndex;
		for (sampleIndex = 0; sampleIndex < NumBytesToRead / 2 && sampleIndex < numSamplesToExtract; sampleIndex++)
		{
			sampleSink[sampleIndex] = *(((int16_t *) source) + sampleIndex) * mult;
		}

		bytesReadOut = sampleIndex * 2;

		return sampleIndex;
	}
}
