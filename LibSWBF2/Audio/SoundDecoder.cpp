#include "Types/List.h"
#include "Logging/Logger.h"
#include "SoundDecoder.h"

#include <iostream>

namespace LibSWBF2
{
	SoundDecoder::SoundDecoder(const Wrappers::Sound* sound)
	{
		p_Sound = const_cast<Wrappers::Sound*>(sound);
	}


	void SoundDecoder::DecodeSingleNibble(int32_t nibble, int32_t &stepIndex, int32_t &predicted)
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



	bool SoundDecoder::DecodeIMAADPCMAndFillPCM16(int16_t *buffer)
	{
		auto DecodedDataBuffer = buffer;
		uint32_t DecodedDataLength = p_Sound -> GetNumChannels() * p_Sound -> GetNumSamples();

		const uint8_t *ADPCMBuffer = p_Sound -> GetDataPtr();
		uint32_t ADPCMBufferLength = p_Sound -> GetDataLength();

		int32_t nibble;
		int destIndex = 0;

		if (p_Sound -> GetNumChannels() == 1)
		{
			int32_t predictor;
			int32_t stepIndex;

			for (uint32_t i = 0; i < ADPCMBufferLength; ++i)
			{
				if (i % 36 == 0)
				{
					predictor = *((int16_t *) (ADPCMBuffer + i));
					stepIndex = *((int16_t *) (ADPCMBuffer + i + 2));

					i+=4;					
				}

				nibble = ADPCMBuffer[i] & 0x0F;
				DecodeSingleNibble(nibble, stepIndex, predictor);
				DecodedDataBuffer[destIndex++] = (int16_t) predictor;

				nibble = (ADPCMBuffer[i] >> 4) & 0x0F;
				DecodeSingleNibble(nibble, stepIndex, predictor);
				DecodedDataBuffer[destIndex++] = (int16_t) predictor;
			}
		}
		else
		{
			int32_t predictorL;
			int32_t stepIndexL;

			int32_t predictorR;
			int32_t stepIndexR;

			int DecodedDataBufferIndex, j;

			// Keeping destination index checks even though I
			for (uint32_t i = 0; i < ADPCMBufferLength; i+=8)
			{	
				if (i % 72 == 0)
				{
					predictorL = *((int16_t *) (ADPCMBuffer + i));
					stepIndexL = *((int16_t *) (ADPCMBuffer + i + 2));

					predictorR = *((int16_t *) (ADPCMBuffer + i + 4));
					stepIndexR = *((int16_t *) (ADPCMBuffer + i + 6));

					i+=8;
				}			


				for (j = 0; j < 4; ++j)
				{
					nibble = ADPCMBuffer[i + j] & 0x0F;
					DecodeSingleNibble(nibble, stepIndexL, predictorL);
					
					DecodedDataBufferIndex = destIndex + 4 * j;
					
					if (DecodedDataBufferIndex >= DecodedDataLength) return true;
					DecodedDataBuffer[DecodedDataBufferIndex] = (int16_t) predictorL;

					nibble = (ADPCMBuffer[i + j] >> 4) & 0x0F;
					DecodeSingleNibble(nibble, stepIndexL, predictorL);

					DecodedDataBufferIndex = destIndex + 4 * j + 2; 
					
					if (DecodedDataBufferIndex >= DecodedDataLength) return true;
					DecodedDataBuffer[DecodedDataBufferIndex] = (int16_t) predictorL;
				}

				for (j = 0; j < 4; ++j)
				{
					nibble = ADPCMBuffer[i + j + 4] & 0x0F;
					DecodeSingleNibble(nibble, stepIndexR, predictorR);
					
					DecodedDataBufferIndex = destIndex + 4 * j + 1;
					
					if (DecodedDataBufferIndex >= DecodedDataLength) return true;
					DecodedDataBuffer[DecodedDataBufferIndex] = (int16_t) predictorR;
					
					nibble = (ADPCMBuffer[i + j + 4] >> 4) & 0x0F;
					DecodeSingleNibble(nibble, stepIndexR, predictorR);
					
					DecodedDataBufferIndex = destIndex + 4 * j + 3;
					
					if (DecodedDataBufferIndex >= DecodedDataLength) return true;
					DecodedDataBuffer[DecodedDataBufferIndex] = (int16_t) predictorR;
				}

				destIndex += 16;
			}
		}

		return true;
	}
}
