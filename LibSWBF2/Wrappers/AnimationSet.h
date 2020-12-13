#pragma once
#include "TranslationFrame.h"
#include "RotationFrame.h"
#include "List.h"
#include "String.h"


namespace LibSWBF2::Wrappers
{
	class LIBSWBF2_API AnimationSet
	{

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