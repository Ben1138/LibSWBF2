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



	int32_t IMAADPCMDecoder::DecodeAndFillPCM16(void * source, uint32_t maxBytes, int16_t * sampleSink, size_t numSamplesToExtract)
	{
		auto DecodedDataBuffer = sampleSink;
		uint32_t DecodedDataLength = numSamplesToExtract; //p_Sound -> GetNumChannels() * p_Sound -> GetNumSamples();

		const uint8_t *ADPCMBuffer = (uint8_t *) source;// p_Sound -> GetDataPtr();
		uint32_t ADPCMBufferLength = maxBytes;

		int32_t nibble;
		int destIndex = 0;

		if (m_NumChannels == 1)
		{
			for (uint32_t i = 0; i < ADPCMBufferLength; ++i)
			{
				if (m_BytesRead % 36 == 0)
				{
					m_Predictor0 = *((int16_t *) (ADPCMBuffer + i));
					m_StepIndex0 = *((int16_t *) (ADPCMBuffer + i + 2));

					i+=4;
					m_BytesRead += 4;					
				}

				nibble = ADPCMBuffer[i] & 0x0F;
				DecodeSingleNibble(nibble, m_StepIndex0, m_Predictor0);
				DecodedDataBuffer[destIndex++] = (int16_t) m_Predictor0;

				nibble = (ADPCMBuffer[i] >> 4) & 0x0F;
				DecodeSingleNibble(nibble, m_StepIndex0, m_Predictor0);
				DecodedDataBuffer[destIndex++] = (int16_t) m_Predictor0;

				m_BytesRead++;
			}
		}
		else
		{
			int DecodedDataBufferIndex, j;

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
					nibble = ADPCMBuffer[i + j] & 0x0F;
					DecodeSingleNibble(nibble, m_StepIndex0, m_Predictor0);
					
					DecodedDataBufferIndex = destIndex + 4 * j;
					
					if (DecodedDataBufferIndex >= DecodedDataLength) return true;
					DecodedDataBuffer[DecodedDataBufferIndex] = (int16_t) m_Predictor0;

					nibble = (ADPCMBuffer[i + j] >> 4) & 0x0F;
					DecodeSingleNibble(nibble, m_StepIndex0, m_Predictor0);

					DecodedDataBufferIndex = destIndex + 4 * j + 2; 
					
					if (DecodedDataBufferIndex >= DecodedDataLength) return true;
					DecodedDataBuffer[DecodedDataBufferIndex] = (int16_t) m_Predictor0;

					m_BytesRead++;
				}


				for (j = 0; j < 4; ++j)
				{
					nibble = ADPCMBuffer[i + j + 4] & 0x0F;
					DecodeSingleNibble(nibble, m_StepIndex1, m_Predictor1);
					
					DecodedDataBufferIndex = destIndex + 4 * j + 1;
					
					if (DecodedDataBufferIndex >= DecodedDataLength) return true;
					DecodedDataBuffer[DecodedDataBufferIndex] = (int16_t) m_Predictor1;
					
					nibble = (ADPCMBuffer[i + j + 4] >> 4) & 0x0F;
					DecodeSingleNibble(nibble, m_StepIndex1, m_Predictor1);
					
					DecodedDataBufferIndex = destIndex + 4 * j + 3;
					
					if (DecodedDataBufferIndex >= DecodedDataLength) return true;
					DecodedDataBuffer[DecodedDataBufferIndex] = (int16_t) m_Predictor1;

					m_BytesRead++;
				}

				destIndex += 16;
			}
		}

		return 1;
	}




	int32_t IMAADPCMDecoder::DecodeAndFillUnity(void * source, uint32_t maxBytes, float * sampleSink, size_t numSamplesToExtract)
	{
		auto DecodedDataBuffer = sampleSink;
		uint32_t DecodedDataLength = numSamplesToExtract; //p_Sound -> GetNumChannels() * p_Sound -> GetNumSamples();

		const uint8_t *ADPCMBuffer = (uint8_t *) source;
		uint32_t ADPCMBufferLength = maxBytes;

		int32_t nibble;
		int destIndex = 0;

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

				nibble = ADPCMBuffer[i] & 0x0F;
				DecodeSingleNibble(nibble, m_StepIndex0, m_Predictor0);
				sampleSink[destIndex++] = fMult * m_Predictor0;

				nibble = (ADPCMBuffer[i] >> 4) & 0x0F;
				DecodeSingleNibble(nibble, m_StepIndex0, m_Predictor0);
				sampleSink[destIndex++] = fMult * m_Predictor0;

				m_BytesRead++;
			}
		}
		else
		{
			int DecodedDataBufferIndex, j;

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
					
					if (DecodedDataBufferIndex >= DecodedDataLength) return true;
					sampleSink[DecodedDataBufferIndex] = fMult * m_Predictor0 ;

					nibble = (ADPCMBuffer[i + j] >> 4) & 0x0F;
					DecodeSingleNibble(nibble, m_StepIndex0, m_Predictor0);

					DecodedDataBufferIndex = destIndex + 4 * j + 2; 
					
					if (DecodedDataBufferIndex >= DecodedDataLength) return true;
					sampleSink[DecodedDataBufferIndex] = fMult * m_Predictor0;

					m_BytesRead++;
				}

				for (j = 0; j < 4; ++j)
				{
					nibble = ADPCMBuffer[i + j + 4] & 0x0F;
					DecodeSingleNibble(nibble, m_StepIndex1, m_Predictor1);
					
					DecodedDataBufferIndex = destIndex + 4 * j + 1;
					
					if (DecodedDataBufferIndex >= DecodedDataLength) return true;
					sampleSink[DecodedDataBufferIndex] = fMult * m_Predictor1;
					
					nibble = (ADPCMBuffer[i + j + 4] >> 4) & 0x0F;
					DecodeSingleNibble(nibble, m_StepIndex1, m_Predictor1);
					
					DecodedDataBufferIndex = destIndex + 4 * j + 3;
					
					if (DecodedDataBufferIndex >= DecodedDataLength) return true;
					sampleSink[DecodedDataBufferIndex] = fMult * m_Predictor1;

					m_BytesRead++;
				}

				destIndex += 16;
			}
		}

		return 1;
	}
}
