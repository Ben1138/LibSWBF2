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
		if (stepIndex > 88)
		{
			stepIndex = 88;
		}
		else if (stepIndex < 0)
		{
			stepIndex = 0;
		}

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
		if (predicted > 0x7FFF)
		{
			predicted = 0x7FFF;
		}
		else if (predicted < -0x8000)
		{
			predicted = -0x8000;
		}
	}



	bool SoundDecoder::DecodeIMAADPCMAndFillPCM16(int16_t *buffer)
	{
		auto finalData = buffer;
		uint32_t finalDataLength = p_Sound -> GetNumChannels() * p_Sound -> GetNumSamples();

		const uint8_t *origData = p_Sound -> GetDataPtr();
		uint32_t len = p_Sound -> GetDataLength() - (p_Sound -> GetNumChannels() == 1 ? 4 : 8);

		int32_t nibble;
		int destIndex = 0;

		if (p_Sound -> GetNumChannels() == 1)
		{
			int32_t predictedValue;
			int32_t stepIndex;

			for (uint32_t i = 0; i < len; ++i)
			{
				if (i % 36 == 0)
				{
					predictedValue = origData[i+0] | (origData[i+1] << 8);
					stepIndex = origData[i+2];
					i+=4;					
				}

				nibble = (origData[i] >> 4) & 0x0F;
				DecodeSingleNibble(nibble, stepIndex, predictedValue);
				finalData[destIndex++] = (int16_t) predictedValue;

				nibble = origData[i] & 0x0F;
				DecodeSingleNibble(nibble, stepIndex, predictedValue);
				finalData[destIndex++] = (int16_t) predictedValue;
			}
		}
		else
		{
			int32_t predictedValueL;
			int32_t stepIndexL;

			int32_t predictedValueR;
			int32_t stepIndexR;

			int finalInd, j;

			// Produces mostly correct result, slightly less distorted than mono...
			for (uint32_t i = 0; i < len; i+=8)
			{	
				if (i % 0x9000 == 0 && i > 0)
				{
					i+=0x9000;
				}


				if (i % 72 == 0)
				{
					predictedValueL = origData[i] | (origData[i+1] << 8);
					stepIndexL = origData[i+2] | (origData[i+3] << 8);

					predictedValueR = origData[i+4] | (origData[i+5] << 8);
					stepIndexR = origData[i+6] | (origData[i+7] << 8);	

					i+=8;
				}			


				for (j = 0; j < 4; ++j)
				{
					nibble = origData[i + j] & 0x0F;
					DecodeSingleNibble(nibble, stepIndexL, predictedValueL);
					
					finalInd = destIndex + 4 * j;
					if (finalInd >= finalDataLength) return true;
					finalData[finalInd] = (int16_t) predictedValueL;

					nibble = (origData[i + j] >> 4) & 0x0F;
					DecodeSingleNibble(nibble, stepIndexL, predictedValueL);

					finalInd = destIndex + 4 * j + 2; 
					if (finalInd >= finalDataLength) return true;
					finalData[finalInd] = (int16_t) predictedValueL;
				}

				for (j = 0; j < 4; ++j)
				{
					nibble = origData[i + j + 4] & 0x0F;
					DecodeSingleNibble(nibble, stepIndexR, predictedValueR);
					finalInd = destIndex + 4 * j + 1;
					if (finalInd >= finalDataLength) return true;
					finalData[finalInd] = (int16_t) predictedValueR;
					
					nibble = (origData[i + j + 4] >> 4) & 0x0F;
					DecodeSingleNibble(nibble, stepIndexR, predictedValueR);
					finalInd = destIndex + 4 * j + 3;
					if (finalInd >= finalDataLength) return true;
					finalData[finalInd] = (int16_t) predictedValueR;
				}

				destIndex += 16;
			}
		}

		return true;
	}
}
