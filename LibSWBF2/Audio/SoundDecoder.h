#pragma once

class SoundDecoder
{
public:
	virtual	void Reset() = 0;
	virtual int32_t DecodeAndFillUnity(void * source, uint32_t maxBytes, float * sampleSink, size_t numSamplesToExtract) = 0;
	virtual int32_t DecodeAndFillPCM16(void * source, uint32_t maxBytes, int16_t * sampleSink, size_t numSamplesToExtract) = 0;
	virtual size_t BytesNeededForSamples(size_t numSamples) = 0;
};