#pragma once
#include "AnimationSet.h"


namespace LibSWBF2::Wrappers
{
	class LIBSWBF2_API AnimationSet
	{


		bool AnimationSet::GetRotationFrames(uint32_t animHash, uint32_t boneHash, List<RotationFrame> &framesOut)
		{
			TNJA *index = animChunk -> p_Bin -> p_JointAddresses;
			TADA *data = animChunk -> p_Bin -> p_CompressedAnimData;
			MINA *metadata = animChunk -> p_Bin -> p_AnimsMetadata;	

			bool animHashExists = true, boneHashExists = true;

			List<uint32_t> &animHashes = animChunk -> p_AnimsMetadata -> m_AnimNameHashes;		

			int animIndex = -1;

			for (int i = 0; i < animHashes.Size(); i++)
			{
				if (animHashes[i] == animHash)
				{
					animIndex = i;

					
				}
			}

			
			return false;
		}




		public:

			String name;

		
			List<uint32_t> GetAnimHashes();
			List<uint32_t> GetBoneHashes(uint32_t animHash);

			List<RotationFrame> GetRotationFrames(uint32_t animHash, uint32_t boneHash);
			List<TranslationFrame> GetTranslationFrames(uint32_t animHash, uint32_t boneHash);

		private:
				
			zaa_ *animChunk;

	};
}