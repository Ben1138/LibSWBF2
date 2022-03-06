#pragma once

class SoundDecoder
{
public:
	virtual	void Reset() = 0;

	// These 2 (and probably more) methods must allow caller to know number of bytes read and samples extracted!
	virtual int32_t DecodeAndFillUnity(void * source, uint32_t maxBytes, float * sampleSink, size_t numSamplesToExtract, size_t& bytesReadOut) = 0;
	virtual int32_t DecodeAndFillPCM16(void * source, uint32_t maxBytes, int16_t * sampleSink, size_t numSamplesToExtract, size_t& bytesReadOut) = 0;
	
	virtual size_t BytesNeededForSamples(size_t numSamples) = 0;
	virtual size_t SamplesInBytes(size_t numBytes) = 0;
};