#pragma once

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
					List<uint16_t> &frame_indices, List<float_t> &frame_values) const;
	
		bool ContainsAnim(uint32_t animHash) const;

		List<uint32_t> GetAnimHashes() const;
		List<uint32_t> GetBoneHashes() const;
		
		bool GetAnimationMetadata(uint32_t animCrc, int &numFrames, int &numBones) const;

		String name;


	private:

		zaa_ *animChunk = nullptr;


		class AnimDecompressor
		{

		private:

			int8_t *buffer;
			int length;

			mutable int read_head;

			mutable float bias, multiplier;


			inline bool ReadInt16(int16_t &val) const
			{
				if (read_head < length - 1)
				{
					val = *((int16_t *) (read_head + buffer));
					read_head += 2;
					return true;
				}
				return false;
			}

			inline bool ReadInt8(int8_t &val) const
			{
				if (read_head < length)
				{
					val = *(read_head + buffer);
					read_head++;
					return true;
				}
				return false;
			}

			inline bool ReadUInt8(uint8_t &val) const
			{
				if (read_head < length)
				{
					val = *((uint8_t *) (read_head + buffer));
					read_head++;
					return true;
				}
				return false;
			}

		public:

			AnimDecompressor(void *_buffer, size_t _length)
			{
				buffer = (int8_t *) _buffer;
				length = _length;
			}

			AnimDecompressor()
			{
				buffer = nullptr;
				length = 0;
			}

			void SetDecompressionParams(float mult = 1.0f / 2047.0f, float offset = 0.0) const
			{
				bias = offset;
				multiplier = mult;
			}

			bool DecompressFromOffset(size_t offset, uint16_t num_frames, 
									List<uint16_t> &frame_indicies, 
									List<float> &frame_values) const
			{
				List<uint16_t> indicies;
				List<float> values;

				read_head = offset;

				uint16_t frame_counter = 0;

				int16_t shortVal;
				int8_t byteVal;
				uint8_t holdDuration;

				float accum = 0.0f;
				
				while (frame_counter < num_frames)
				{
					if (!ReadInt16(shortVal)) return false;

					accum = bias + multiplier * (float) shortVal;

					indicies.Add(frame_counter);
					values.Add(accum);

					frame_counter++;


					while (frame_counter < num_frames)
					{
						if (!ReadInt8(byteVal)) return false;

						// Signals to hold accumulator for x frames,
						// x specified by the next (unsigned) byte.
						if (byteVal == -0x80)
						{
							if (!ReadUInt8(holdDuration)) return false;
							//frame_counter += holdDuration;

							for (int i = 0; i < holdDuration; i++)
							{
								indicies.Add(frame_counter++);
								values.Add(accum);
							}

							//break;
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
							accum += multiplier * (float) byteVal;

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