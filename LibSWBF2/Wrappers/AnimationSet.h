#pragma once
#include "stdafx.h"
#include "req.h"
//#include "Types/LibString.h"
//#include "Types/List.h"

#include "Chunks/LVL/zaa_/zaa_.h"



namespace LibSWBF2::Wrappers
{
	using Types::List;
	using Types::String;
	using namespace Chunks::LVL::animation;


	class LIBSWBF2_API AnimationSet
	{

	public:

		static bool FromChunk(zaa_ *chunk, AnimationSet &setOut);

		bool GetCurve(uint32_t animHash, uint32_t boneHash, uint16_t component,
					List<uint16_t> &frame_indices, List<float_t> &frame_values);
	
		bool ContainsAnim(uint32_t animHash);

		String name;

		//List<uint32_t> GetAnimHashes();
		//List<uint32_t> GetBoneHashes(uint32_t animHash);


	private:

		zaa_ *animChunk = nullptr;


		class AnimDecompressor
		{

		private:

			int8_t *buffer;
			size_t read_head;
			size_t length;

			float bias, multiplier;


			inline bool ReadInt16(int16_t &val)
			{
				if (read_head < length - 1)
				{
					val = *((int16_t *) (read_head + buffer));
					read_head += 2;
					return true;
				}
				return false;
			}

			inline bool ReadInt8(int8_t &val)
			{
				if (read_head < length)
				{
					val = *(read_head + buffer);
					read_head++;
					return true;
				}
				return false;
			}

		public:

			AnimDecompressor(void *buffer, size_t length)
			{
				buffer = (int8_t *) buffer;
				length = length;
			}

			AnimDecompressor()
			{
				buffer = nullptr;
				length = 0;
			}

			void SetDecompressionParams(float mult = 1.0f / 2047.0f, float offset = 0.0)
			{
				bias = offset;
				multiplier = mult;
			}

			bool DecompressFromOffset(size_t offset, uint16_t num_frames, 
									List<uint16_t> &frame_indicies, 
									List<float> &frame_values)
			{
				List<uint16_t> indicies;
				List<float> values;

				read_head = offset;

				uint16_t frame_counter = 0;

				int16_t shortVal;
				int8_t byteVal;

				float accum = 0.0f;

				while (frame_counter < num_frames)
				{
					if (!ReadInt16(shortVal)) return false;

					accum = bias + multiplier * shortVal;

					indicies.Add(frame_counter);
					values.Add(accum);

					frame_counter++;


					while (frame_counter < num_frames)
					{
						if (!ReadInt8(byteVal)) return false;

						// Signals to hold accumulator for x frames,
						// x specified by the next byte.
						if (byteVal == -0x80)
						{
							if (!ReadInt8(byteVal)) return false;
							frame_counter += byteVal;
							break;
						}

						// Signals to reset the accumulator to the value
						// of the next decompressed short.
						else if (byteVal == -0x7f)
						{
							break;
						}

						// Increment the accumulator by the value
						// of the next decompressed byte.  Decomp here
						// does not apply the offset, only the multiplier.
						else 
						{
							accum += multiplier * byteVal;

							indicies.Add(frame_counter);
							values.Add(accum);

							frame_counter++;
						}
					}
				}

				frame_indicies = std::move(indicies);
				frame_values   = std::move(values); 

				return true;
			}
		};

		AnimDecompressor decompressor;
	};
}