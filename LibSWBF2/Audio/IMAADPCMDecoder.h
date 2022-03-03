#pragma once

#include "Types/List.h"
#include "Logging/Logger.h"
#include "Wrappers/Sound.h"
#include "SoundDecoder.h"


/*
Until a different stream format is encountered, 
this class will only handle IMAADPCM -> Unity & IMAADPCM -> PCM16.

This class does one thing (decodes IMA-ADPCM data to a preallocated buffer)
in different contexts (converting Sound data in memory and converting SoundStream data from disk)
*/


namespace LibSWBF2
{
	class IMAADPCMDecoder : public SoundDecoder
	{
		constexpr static int ima_index_table[16] = 
		{
		  -1, -1, -1, -1, 2, 4, 6, 8,
		  -1, -1, -1, -1, 2, 4, 6, 8
		}; 

		constexpr static int ima_step_table[89] = 
		{ 
		  7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 
		  19, 21, 23, 25, 28, 31, 34, 37, 41, 45, 
		  50, 55, 60, 66, 73, 80, 88, 97, 107, 118, 
		  130, 143, 157, 173, 190, 209, 230, 253, 279, 307,
		  337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
		  876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066, 
		  2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358,
		  5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899, 
		  15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767 
		}; 

		constexpr static float fMult = 1.0f / 32768.0f;

		private:

			void DecodeSingleNibble(int32_t nibble, int32_t &stepIndex, int32_t &predicted);

			int m_NumChannels;
			int m_ChannelInterleave;

			int32_t m_StepIndex0, m_Predictor0;
			int32_t m_StepIndex1, m_Predictor1;

			int m_BytesRead;


		public:

			IMAADPCMDecoder(int numChannels, int channelInterleave);

			void Reset();

			int32_t DecodeAndFillUnity(void * source, uint32_t maxBytes, float * sampleSink, size_t numSamplesToExtract);
			int32_t DecodeAndFillPCM16(void * source, uint32_t maxBytes, int16_t * sampleSink, size_t numSamplesToExtract);
	
			size_t BytesNeededForSamples(size_t numSamples);
	};
}
