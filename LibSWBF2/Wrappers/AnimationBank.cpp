#include "req.h"
#include "pch.h"

#include "AnimationBank.h"
#include "Chunks/LVL/zaa_/zaa_.h"

#include "InternalHelpers.h"



namespace LibSWBF2::Wrappers
{
	// AnimDecompressor

	class AnimDecompressor
	{

	public:

		AnimDecompressor(void * buf, size_t len) : p_Buffer((int8_t *) buf), m_Length(len){}
		AnimDecompressor() : p_Buffer(nullptr), m_Length(0) {}

		void SetDecompressionParams(float_t mult = 1.0f / 2047.0f, float_t offset = 0.0) const
		{
			m_Bias = offset;
			m_Multiplier = mult;
		}

		bool DecompressFromOffset(size_t offset, uint16_t num_frames, 
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

		AnimDecompressor(const AnimDecompressor &) = default;	


	private:

		int8_t *p_Buffer;
		size_t m_Length;

		mutable size_t m_ReadHead;
		mutable float_t m_Bias, m_Multiplier;

		inline bool ReadInt16(int16_t &val) const
		{
			if (m_ReadHead < m_Length - 1)
			{
				val = *((int16_t *) (m_ReadHead + p_Buffer));
				m_ReadHead += 2;
				return true;
			}
			return false;
		}

		inline bool ReadInt8(int8_t &val) const
		{
			if (m_ReadHead < m_Length)
			{
				val = *(m_ReadHead + p_Buffer);
				m_ReadHead++;
				return true;
			}
			return false;
		}

		inline bool ReadUInt8(uint8_t &val) const
		{
			if (m_ReadHead < m_Length)
			{
				val = *((uint8_t *) (m_ReadHead + p_Buffer));
				m_ReadHead++;
				return true;
			}
			return false;
		}
	};


		

	// AnimationBank

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
		setOut.p_Decompressor = new AnimDecompressor(
								(void *) chunk -> p_Bin -> p_CompressedAnimData -> p_DataBuffer,
								chunk -> p_Bin -> p_CompressedAnimData -> m_DataBufferLength
							);

		return true;
	}


	AnimationBank& AnimationBank::operator=(const AnimationBank& other)
	{
		p_AnimChunk = other.p_AnimChunk;
		p_Decompressor = new AnimDecompressor(*other.p_Decompressor);		
		return *this;
	}


	AnimationBank::~AnimationBank()
	{
		delete p_Decompressor;
	}


	const String& AnimationBank::GetName() const
	{
		return p_AnimChunk -> p_Name -> m_Text;
	}
	

	bool AnimationBank::ContainsAnimation(CRCChecksum animName) const
	{
		return p_AnimChunk -> p_Bin -> p_AnimsMetadata -> m_AnimNameHashes.Contains(animName);
	}


	List<CRCChecksum> AnimationBank::GetAnimations() const
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


	List<CRCChecksum> AnimationBank::GetBones() const
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

		uint32_t TNJAOffset = 0;	

		for (uint32_t i = 0; i < animCRCs.Size(); i++)
		{
			if (animCRCs[i] == animName)
			{
				uint32_t num_bones = metadata -> m_AnimBoneCounts[i];
				uint16_t num_frames = metadata -> m_AnimFrameCounts[i];	

				//Some zaabin files have duplicate entries for bones in TNJA.
				//The latter of the two is correct, so we try to find it first...

				uint32_t tempOffset = TNJAOffset;
				uint32_t foundBone = false;
				for (uint32_t j = 0; j < num_bones; j++)
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


				uint32_t TADAOffset;

				if (component < 4)
				{
					p_Decompressor -> SetDecompressionParams();
					TADAOffset = index -> m_RotationOffsets[TNJAOffset * 4 + component];
				}
				else
				{
					float_t bias = index -> m_TranslationParams[4 * TNJAOffset + component - 4];
					float_t mult = index -> m_TranslationParams[4 * TNJAOffset + 3];

					p_Decompressor -> SetDecompressionParams(mult, bias);
					TADAOffset = index -> m_TranslationOffsets[TNJAOffset * 3 + component - 4];
				}

				decompStatus = p_Decompressor -> DecompressFromOffset(
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


	Curve<uint16_t> AnimationBank::GetCurve(CRCChecksum anim, CRCChecksum bone, ECurveType comp) const
	{
		List<uint16_t> inds;
		List<float_t> values;

		if (GetCurve(anim, bone, (uint32_t) comp, inds, values))
		{
			return Curve<uint16_t>(std::move(inds), std::move(values));
		}
		else 
		{
			LOG_THROW("AnimationBank {0}: Error decompressing curve for bone: 0x{1:x} of animation 0x{2:x}", GetName().Buffer(), bone, anim);
		}
	}
}

