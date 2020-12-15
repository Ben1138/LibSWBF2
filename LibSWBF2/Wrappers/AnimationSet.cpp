#include "AnimationSet.h"

#include "Chunks/LVL/zaa_/BIN_.h"
#include "Chunks/LVL/zaa_/TADA.h"
#include "Chunks/LVL/zaa_/TNJA.h"
#include "Chunks/LVL/zaa_/MINA.h"


namespace LibSWBF2::Wrappers
{
	using namespace Chunks::LVL::animation;

	bool AnimationSet::FromChunk(zaa_ *chunk, AnimationSet &setOut)
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
	

	bool AnimationSet::ContainsAnim(uint32_t animHash) const
	{
		return animChunk -> p_Bin -> p_AnimsMetadata -> m_AnimNameHashes.Contains(animHash);
	}

	List<uint32_t> AnimationSet::GetAnimHashes() const
	{
		return animChunk -> p_Bin -> p_AnimsMetadata -> m_AnimNameHashes;
	}

	List<uint32_t> AnimationSet::GetBoneHashes() const
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
	

	bool AnimationSet::GetCurve(uint32_t animHash, uint32_t boneHash, uint16_t component,
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

				for (int j = 0; j < num_bones; j++)
				{
					if (index -> m_BoneCRCs[TNJAOffset] == boneHash)
					{
						int TADAOffset;

						if (component < 4)
						{
							decompressor.SetDecompressionParams();
							TADAOffset = index -> m_RotationOffsets[TNJAOffset * 4 + component];
						}
						else
						{
							float mult = index -> m_TranslationParams[4 * TNJAOffset + component - 4];
							float bias = index -> m_TranslationParams[4 * TNJAOffset + 3];

							decompressor.SetDecompressionParams(bias, mult);
							TADAOffset = index -> m_TranslationOffsets[TNJAOffset * 3 + component - 4];
						}

						decompStatus = decompressor.DecompressFromOffset(
												TADAOffset, num_frames, 
												frame_indices, 
												frame_values
											);
						break;
					}
					else 
					{
						TNJAOffset++;
					}
				}

				break;			
			}
			else 
			{
				TNJAOffset += metadata -> m_AnimBoneCounts[i];
			}
		}

		return decompStatus;
	}
}