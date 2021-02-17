#include "stdafx.h"
#include "req.h"

#include "AnimationBank.h"

#include "Chunks/LVL/zaa_/BIN_.h"
#include "Chunks/LVL/zaa_/TADA.h"
#include "Chunks/LVL/zaa_/TNJA.h"
#include "Chunks/LVL/zaa_/MINA.h"


using LibSWBF2::Types::List;


namespace LibSWBF2::Wrappers
{
	inline bool AnimationBank::AnimDecompressor::ReadInt16(int16_t &val) const
	{
		if (m_ReadHead < m_Length - 1)
		{
			val = *((int16_t *) (m_ReadHead + p_Buffer));
			m_ReadHead += 2;
			return true;
		}
		return false;
	}

	inline bool AnimationBank::AnimDecompressor::ReadInt8(int8_t &val) const
	{
		if (m_ReadHead < m_Length)
		{
			val = *(m_ReadHead + p_Buffer);
			m_ReadHead++;
			return true;
		}
		return false;
	}

	inline bool AnimationBank::AnimDecompressor::ReadUInt8(uint8_t &val) const
	{
		if (m_ReadHead < m_Length)
		{
			val = *((uint8_t *) (m_ReadHead + p_Buffer));
			m_ReadHead++;
			return true;
		}
		return false;
	}

	AnimationBank::AnimDecompressor::AnimDecompressor(void *_buffer, size_t _length)
	{
		p_Buffer = (int8_t *) _buffer;
		m_Length = _length;
	}

	AnimationBank::AnimDecompressor::AnimDecompressor()
	{
		p_Buffer = nullptr;
		m_Length = 0;
	}

	void AnimationBank::AnimDecompressor::SetDecompressionParams(float_t mult, float_t offset) const
	{
		m_Bias = offset;
		m_Multiplier = mult;
	}

	bool AnimationBank::AnimDecompressor::DecompressFromOffset(size_t offset, uint16_t num_frames, 
							List<uint16_t> &frame_indicies, 
							List<float_t> &frame_values) const
	{
		List<uint16_t> indicies;
		List<float_t> values;

		m_ReadHead = offset;

		uint16_t frame_counter = 0;

		int16_t shortVal;
		int8_t byteVal;
		uint8_t holdDuration;

		float accum = 0.0f;
		
		while (frame_counter < num_frames)
		{
			if (!ReadInt16(shortVal)) return false;

			accum = m_Bias + m_Multiplier * (float) shortVal;

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

				#ifndef _ANIM_DEBUG
					frame_counter += holdDuration;
				#else
					for (int i = 0; i < holdDuration; i++)
					{
						indicies.Add(frame_counter);
						values.Add(accum);

						frame_counter++;
					}
				#endif
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
					accum += m_Multiplier * (float) byteVal;

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




	using namespace Chunks::LVL::animation;

	bool AnimationBank::FromChunk(zaa_ *chunk, AnimationBank &setOut)
	{
		if (chunk == nullptr)
		{
			return false;
		}
		else 
		{
			if ((chunk -> p_Bin == nullptr) ||
				(chunk -> p_Bin -> p_CompressedAnimData == nullptr) ||
				(chunk -> p_Bin -> p_JointAddresses == nullptr) ||
				(chunk -> p_Bin -> p_AnimsMetadata == nullptr) ||
				(chunk -> p_Name == nullptr))
			{
				return false;
			}
		}

		setOut.p_AnimChunk = chunk;
		setOut.m_Decompressor = AnimDecompressor(
								(void *) chunk -> p_Bin -> p_CompressedAnimData -> p_DataBuffer,
								chunk -> p_Bin -> p_CompressedAnimData -> m_DataBufferLength
							);

		return true;
	}

	const String& AnimationBank::GetName() const
	{
		return p_AnimChunk -> p_Name -> m_Text;
	}
	

	bool AnimationBank::ContainsAnimation(CRCChecksum animName) const
	{
		return p_AnimChunk -> p_Bin -> p_AnimsMetadata -> m_AnimNameHashes.Contains(animName);
	}


	List<CRCChecksum> AnimationBank::GetAnimationNames() const
	{
		return p_AnimChunk -> p_Bin -> p_AnimsMetadata -> m_AnimNameHashes;
	}


	bool AnimationBank::GetAnimationMetadata(CRCChecksum animCRC, uint32_t &numFrames, uint32_t &numBones) const
	{
		MINA *metadata = p_AnimChunk -> p_Bin -> p_AnimsMetadata;	

		List<CRCChecksum> &animCRCs = metadata -> m_AnimNameHashes;	

		for (int i = 0; i < animCRCs.Size(); i++)
		{
			if (animCRCs[i] == animCRC)
			{
				numBones  = (uint32_t) metadata -> m_AnimBoneCounts[i];
				numFrames = (uint32_t) metadata -> m_AnimFrameCounts[i];	
				return true;
			}
		}

		return false;
	}


	List<CRCChecksum> AnimationBank::GetBoneNames() const
	{
		TNJA *index = p_AnimChunk -> p_Bin -> p_JointAddresses;

		List<CRCChecksum> boneHashes;

		int num_bones = p_AnimChunk -> p_Bin -> p_AnimsMetadata -> m_AnimBoneCounts[0];

		for (int i = 0; i < num_bones; i++)
		{
			boneHashes.Add(index -> m_BoneCRCs[i]);
		}

		return boneHashes;
	}
	

	bool AnimationBank::GetCurve(CRCChecksum animName, CRCChecksum boneName, uint16_t component,
										List<uint16_t> &frame_indices, List<float_t> &frame_values) const
	{
		TNJA *index = p_AnimChunk -> p_Bin -> p_JointAddresses;
		TADA *data = p_AnimChunk -> p_Bin -> p_CompressedAnimData;
		MINA *metadata = p_AnimChunk -> p_Bin -> p_AnimsMetadata;	

		bool decompStatus = false;

		List<float_t> values;
		List<uint16_t> indicies;

		List<CRCChecksum> &animCRCs = metadata -> m_AnimNameHashes;	

		int TNJAOffset = 0;	

		for (int i = 0; i < animCRCs.Size(); i++)
		{
			if (animCRCs[i] == animName)
			{
				int num_bones = metadata -> m_AnimBoneCounts[i];
				uint16_t num_frames = metadata -> m_AnimFrameCounts[i];	

				//Some zaabin files have duplicate entries for bones in TNJA.
				//The latter of the two is correct, so we try to find it first...

				int tempOffset = TNJAOffset;
				bool foundBone = false;
				for (int j = 0; j < num_bones; j++)
				{
					if (index -> m_BoneCRCs[tempOffset] == boneName)
					{
						foundBone = true;
						TNJAOffset = tempOffset;
					}

					tempOffset++;
				}

				if (!foundBone)
				{
					return false;
				}


				int TADAOffset;

				if (component < 4)
				{
					m_Decompressor.SetDecompressionParams();
					TADAOffset = index -> m_RotationOffsets[TNJAOffset * 4 + component];
				}
				else
				{
					float bias = index -> m_TranslationParams[4 * TNJAOffset + component - 4];
					float mult = index -> m_TranslationParams[4 * TNJAOffset + 3];

					m_Decompressor.SetDecompressionParams(mult, bias);
					TADAOffset = index -> m_TranslationOffsets[TNJAOffset * 3 + component - 4];
				}

				decompStatus = m_Decompressor.DecompressFromOffset(
										TADAOffset, num_frames, 
										frame_indices, 
										frame_values
									);	
			}
			else 
			{
				TNJAOffset += metadata -> m_AnimBoneCounts[i];
			}
		}

		return decompStatus;
	}
}