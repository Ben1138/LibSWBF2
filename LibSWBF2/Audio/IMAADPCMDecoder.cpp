#include "Types/List.h"
#include "Logging/Logger.h"
#include "IMAADPCMDecoder.h"

#include <iostream>

namespace LibSWBF2
{
	IMAADPCMDecoder::IMAADPCMDecoder(int numChannels, int channelInterleave)
	{
		m_NumChannels = numChannels;
		m_ChannelInterleave = channelInterleave;
		m_BytesRead  = 0;
		m_StepIndex0 = 0;
		m_Predictor0 = 0;
		m_StepIndex1 = 0;
		m_Predictor1 = 0;
	}

	void IMAADPCMDecoder::Reset()
	{
		m_BytesRead  = 0;
		m_StepIndex0 = 0;
		m_Predictor0 = 0;
		m_StepIndex1 = 0;
		m_Predictor1 = 0;
	}


	size_t IMAADPCMDecoder::BytesNeededForSamples(size_t numSamples)
	{
		numSamples += numSamples % 2 == 0 ? 0 : 1;

		size_t BlockSize = m_NumChannels * 36;
		size_t BlockHeaderSize = m_NumChannels * 4;
		size_t SamplesPerBlock = m_NumChannels * 32 * 2;

		size_t BytesLeftInBlock = (BlockSize - (m_BytesRead % BlockSize)) % BlockSize;

		size_t NumSampleBytes = numSamples / 2;

		if (NumSampleBytes <= BytesLeftInBlock)
		{
			return NumSampleBytes;
		}
		else 
		{
			return NumSampleBytes + ((NumSampleBytes - BytesLeftInBlock) / (m_NumChannels * 32) + 1) * BlockHeaderSize;
		}
	}


	size_t IMAADPCMDecoder::SamplesInBytes(size_t numBytes)
	{
		int BlockSize = m_NumChannels * 36;

		if (numBytes % BlockSize != 0) return 0;

		return (numBytes / BlockSize) * m_NumChannels * 64;
	}




	void IMAADPCMDecoder::DecodeSingleNibble(int32_t nibble, int32_t &stepIndex, int32_t &predicted)
	{
		int32_t step = ima_step_table[stepIndex];

		stepIndex += ima_index_table[nibble];

		// Clamp new index to step table size
		stepIndex = stepIndex > 88 ? 88 : stepIndex < 0 ? 0 : stepIndex;

		// Below is the optimized version which avoids the float division/mult
		int32_t delta = step >> 3;

		if (nibble & 4)
		{
			delta += step;
		}
		if (nibble & 2)
		{
			delta += step >> 1;
		}
		if (nibble & 1)
		{
			delta += step >> 2;
		}
		if (nibble & 8)
		{
			predicted -= delta;
		}
		else
		{
			predicted += delta;
		}

		// Clamp to int16 boundaries (since PCM16 is our testing destination)
		predicted = predicted > 0x7FFF ? 0x7FFF : predicted < -0x8000 ? -0x8000 : predicted;
	}



	int32_t IMAADPCMDecoder::DecodeAndFillPCM16(void * source, uint32_t maxBytes, int16_t * sampleSink, size_t numSamplesToExtract, size_t& bytesReadOut)
	{
		auto DecodedDataBuffer = sampleSink;

		const uint8_t *ADPCMBuffer = (uint8_t *) source;
		uint32_t ADPCMBufferLength = maxBytes;

		int32_t nibble;
		int destIndex = 0;

		bytesReadOut = m_BytesRead;

		int32_t NumSamplesRead = 0;

		int DecodedDataBufferIndex = 0;


		if (m_NumChannels == 1)
		{
			// This loop is safe because the munger is guaranteed to fill out partial blocks
			for (uint32_t i = 0; i < ADPCMBufferLength; ++i)
			{
				if (m_BytesRead % 36 == 0)
				{
					m_Predictor0 = *((int16_t *) (ADPCMBuffer + i));
					m_StepIndex0 = *((int16_t *) (ADPCMBuffer + i + 2));

					i+=4;
					m_BytesRead += 4;					
				}

				m_BytesRead++;

				nibble = ADPCMBuffer[i] & 0x0F;
				DecodeSingleNibble(nibble, m_StepIndex0, m_Predictor0);
				DecodedDataBuffer[DecodedDataBufferIndex++] = (int16_t) m_Predictor0;

				NumSamplesRead++;

				if (DecodedDataBufferIndex >= numSamplesToExtract) break;

				nibble = (ADPCMBuffer[i] >> 4) & 0x0F;
				DecodeSingleNibble(nibble, m_StepIndex0, m_Predictor0);
				DecodedDataBuffer[DecodedDataBufferIndex++] = (int16_t) m_Predictor0;

				NumSamplesRead++;

				if (DecodedDataBufferIndex >= numSamplesToExtract) break;
			}
		}
		else
		{
			int j;
			// Keeping destination index checks even though I
			for (uint32_t i = 0; i < ADPCMBufferLength; i+=8)
			{	
				if (m_BytesRead % 72 == 0)
				{
					m_Predictor0 = *((int16_t *) (ADPCMBuffer + i));
					m_StepIndex0 = *((int16_t *) (ADPCMBuffer + i + 2));

					m_Predictor1 = *((int16_t *) (ADPCMBuffer + i + 4));
					m_StepIndex1 = *((int16_t *) (ADPCMBuffer + i + 6));

					i+=8;
					m_BytesRead += 8;
				}

				for (j = 0; j < 4; ++j)
				{
					m_BytesRead++;

					nibble = ADPCMBuffer[i + j] & 0x0F;
					DecodeSingleNibble(nibble, m_StepIndex0, m_Predictor0);
					
					DecodedDataBufferIndex = destIndex + 4 * j;
					
					if (DecodedDataBufferIndex >= numSamplesToExtract) break;

					NumSamplesRead++;

					DecodedDataBuffer[DecodedDataBufferIndex] = (int16_t) m_Predictor0;

					nibble = (ADPCMBuffer[i + j] >> 4) & 0x0F;
					DecodeSingleNibble(nibble, m_StepIndex0, m_Predictor0);

					DecodedDataBufferIndex = destIndex + 4 * j + 2; 
					
					if (DecodedDataBufferIndex >= numSamplesToExtract) break;

					NumSamplesRead++;

					DecodedDataBuffer[DecodedDataBufferIndex] = (int16_t) m_Predictor0;

				}

				for (j = 0; j < 4; ++j)
				{
					nibble = ADPCMBuffer[i + j + 4] & 0x0F;
					DecodeSingleNibble(nibble, m_StepIndex1, m_Predictor1);
					
					DecodedDataBufferIndex = destIndex + 4 * j + 1;
					
					if (DecodedDataBufferIndex >= numSamplesToExtract) break;

					NumSamplesRead++;

					DecodedDataBuffer[DecodedDataBufferIndex] = (int16_t) m_Predictor1;
					
					nibble = (ADPCMBuffer[i + j + 4] >> 4) & 0x0F;
					DecodeSingleNibble(nibble, m_StepIndex1, m_Predictor1);
					
					DecodedDataBufferIndex = destIndex + 4 * j + 3;
					
					if (DecodedDataBufferIndex >= numSamplesToExtract) break;

					NumSamplesRead++;

					DecodedDataBuffer[DecodedDataBufferIndex] = (int16_t) m_Predictor1;

					m_BytesRead++;
				}

				destIndex += 16;
			}
		}

		bytesReadOut = m_BytesRead - bytesReadOut;

		return NumSamplesRead;
	}




	int32_t IMAADPCMDecoder::DecodeAndFillUnity(void * source, uint32_t maxBytes, float * sampleSink, size_t numSamplesToExtract, size_t& bytesReadOut)
	{
		auto DecodedDataBuffer = sampleSink;
		uint32_t DecodedDataLength = numSamplesToExtract;

		const uint8_t *ADPCMBuffer = (uint8_t *) source;
		uint32_t ADPCMBufferLength = maxBytes;

		int32_t nibble;

		bytesReadOut = m_BytesRead;

		int32_t NumSamplesRead = 0;

		int DecodedDataBufferIndex = 0;


		if (m_NumChannels == 1)
		{
			for (uint32_t i = 0; i < ADPCMBufferLength; ++i)
			{
				if (m_BytesRead % 36 == 0)
				{
					m_Predictor0 = *((int16_t *) (ADPCMBuffer + i));
					m_StepIndex0 = *((int16_t *) (ADPCMBuffer + i + 2));

					i+=4;
					m_BytesRead+=4;					
				}

				m_BytesRead++;

				nibble = ADPCMBuffer[i] & 0x0F;
				DecodeSingleNibble(nibble, m_StepIndex0, m_Predictor0);

				if (DecodedDataBufferIndex >= numSamplesToExtract) break;

				NumSamplesRead++;

				sampleSink[DecodedDataBufferIndex++] = fMult * m_Predictor0;

				nibble = (ADPCMBuffer[i] >> 4) & 0x0F;
				DecodeSingleNibble(nibble, m_StepIndex0, m_Predictor0);

				if (DecodedDataBufferIndex >= numSamplesToExtract) break;

				NumSamplesRead++;

				sampleSink[DecodedDataBufferIndex++] = fMult * m_Predictor0;
			}
		}
		else
		{
			int j;
			int destIndex = 0;

			// Keeping destination index checks even though I
			for (uint32_t i = 0; i < ADPCMBufferLength; i+=8)
			{	
				if (m_BytesRead % 72 == 0)
				{
					m_Predictor0 = *((int16_t *) (ADPCMBuffer + i));
					m_StepIndex0 = *((int16_t *) (ADPCMBuffer + i + 2));

					m_Predictor1 = *((int16_t *) (ADPCMBuffer + i + 4));
					m_StepIndex1 = *((int16_t *) (ADPCMBuffer + i + 6));

					i+=8;
					m_BytesRead+=8;
				}			


				for (j = 0; j < 4; ++j)
				{
					nibble = ADPCMBuffer[i + j] & 0x0F;
					DecodeSingleNibble(nibble, m_StepIndex0, m_Predictor0);
					
					DecodedDataBufferIndex = destIndex + 4 * j;

					if (DecodedDataBufferIndex >= numSamplesToExtract) break;

					NumSamplesRead++;

					sampleSink[DecodedDataBufferIndex] = fMult * m_Predictor0 ;

					nibble = (ADPCMBuffer[i + j] >> 4) & 0x0F;
					DecodeSingleNibble(nibble, m_StepIndex0, m_Predictor0);

					DecodedDataBufferIndex = destIndex + 4 * j + 2; 
					
					if (DecodedDataBufferIndex >= numSamplesToExtract) break;

					NumSamplesRead++;


					sampleSink[DecodedDataBufferIndex] = fMult * m_Predictor0;

					m_BytesRead++;
				}

				for (j = 0; j < 4; ++j)
				{
					nibble = ADPCMBuffer[i + j + 4] & 0x0F;
					DecodeSingleNibble(nibble, m_StepIndex1, m_Predictor1);
					
					DecodedDataBufferIndex = destIndex + 4 * j + 1;
					
					if (DecodedDataBufferIndex >= numSamplesToExtract) break;

					NumSamplesRead++;

					sampleSink[DecodedDataBufferIndex] = fMult * m_Predictor1;

					
					nibble = (ADPCMBuffer[i + j + 4] >> 4) & 0x0F;
					DecodeSingleNibble(nibble, m_StepIndex1, m_Predictor1);
					
					DecodedDataBufferIndex = destIndex + 4 * j + 3;
					
					if (DecodedDataBufferIndex >= numSamplesToExtract) break;

					NumSamplesRead++;

					sampleSink[DecodedDataBufferIndex] = fMult * m_Predictor1;

					m_BytesRead++;
				}

				destIndex += 16;
			}
		}

		bytesReadOut = m_BytesRead - bytesReadOut;

		return NumSamplesRead;
	}
}
