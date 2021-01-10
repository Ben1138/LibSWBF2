#include "stdafx.h"
#include "req.h"

#include "AnimationBank.h"

#include "Chunks/LVL/zaa_/BIN_.h"
#include "Chunks/LVL/zaa_/TADA.h"
#include "Chunks/LVL/zaa_/TNJA.h"
#include "Chunks/LVL/zaa_/MINA.h"



namespace LibSWBF2::Wrappers
{
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
				(chunk -> p_Bin -> p_AnimsMetadata == nullptr))
			{
				return false;
			}
		}

		setOut.animChunk = chunk;
		setOut.name = chunk -> p_Name -> m_Text;

		setOut.decompressor = AnimDecompressor(
								(void *) chunk -> p_Bin -> p_CompressedAnimData -> p_DataBuffer,
								chunk -> p_Bin -> p_CompressedAnimData -> m_DataBufferLength
							);

		return true;
	}
	

	bool AnimationBank::ContainsAnim(uint32_t animHash) const
	{
		return animChunk -> p_Bin -> p_AnimsMetadata -> m_AnimNameHashes.Contains(animHash);
	}


	List<uint32_t> AnimationBank::GetAnimHashes() const
	{
		return animChunk -> p_Bin -> p_AnimsMetadata -> m_AnimNameHashes;
	}


	bool AnimationBank::GetAnimationMetadata(uint32_t animCRC, int &numFrames, int &numBones) const
	{
		MINA *metadata = animChunk -> p_Bin -> p_AnimsMetadata;	

		List<uint32_t> &animHashes = metadata -> m_AnimNameHashes;	

		for (int i = 0; i < animHashes.Size(); i++)
		{
			if (animHashes[i] == animCRC)
			{
				numBones  = (int) metadata -> m_AnimBoneCounts[i];
				numFrames = (int) metadata -> m_AnimFrameCounts[i];	
				return true;
			}
		}

		return false;
	}


	List<uint32_t> AnimationBank::GetBoneHashes() const
	{
		TNJA *index = animChunk -> p_Bin -> p_JointAddresses;

		List<uint32_t> boneHashes;

		int num_bones = animChunk -> p_Bin -> p_AnimsMetadata -> m_AnimBoneCounts[0];

		for (int i = 0; i < num_bones; i++)
		{
			boneHashes.Add(index -> m_BoneCRCs[i]);
		}

		return boneHashes;
	}
	

	bool AnimationBank::GetCurve(uint32_t animHash, uint32_t boneHash, uint16_t component,
										List<uint16_t> &frame_indices, List<float_t> &frame_values) const
	{
		TNJA *index = animChunk -> p_Bin -> p_JointAddresses;
		TADA *data = animChunk -> p_Bin -> p_CompressedAnimData;
		MINA *metadata = animChunk -> p_Bin -> p_AnimsMetadata;	

		bool decompStatus = false;

		List<float_t> values;
		List<uint16_t> indicies;

		List<uint32_t> &animHashes = metadata -> m_AnimNameHashes;	

		int TNJAOffset = 0;	

		for (int i = 0; i < animHashes.Size(); i++)
		{
			if (animHashes[i] == animHash)
			{
				int num_bones = metadata -> m_AnimBoneCounts[i];
				uint16_t num_frames = metadata -> m_AnimFrameCounts[i];	

				//Some zaabin files have duplicate entries for bones in TNJA.
				//The latter of the two is correct, so we try to find it first...

				int tempOffset = TNJAOffset;
				bool foundBone = false;
				for (int j = 0; j < num_bones; j++)
				{
					if (index -> m_BoneCRCs[tempOffset] == boneHash)
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
					decompressor.SetDecompressionParams();
					TADAOffset = index -> m_RotationOffsets[TNJAOffset * 4 + component];
				}
				else
				{
					float bias = index -> m_TranslationParams[4 * TNJAOffset + component - 4];
					float mult = index -> m_TranslationParams[4 * TNJAOffset + 3];

					decompressor.SetDecompressionParams(mult, bias);
					TADAOffset = index -> m_TranslationOffsets[TNJAOffset * 3 + component - 4];
				}

				decompStatus = decompressor.DecompressFromOffset(
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