#pragma once
#include "Chunks/LVL/zaa_/zaa_.h"



namespace LibSWBF2::Wrappers
{
	using Types::List;
	using Types::String;
	using namespace Chunks::LVL::animation;


	class LIBSWBF2_API AnimationBank
	{
		friend List<AnimationBank>;

	public:

		static bool FromChunk(zaa_ *chunk, AnimationBank &setOut);

		bool GetCurve(CRCChecksum anim, CRCChecksum bone, uint16_t component,
					List<uint16_t> &frame_indices, List<float_t> &frame_values) const;
	
		bool ContainsAnimation(CRCChecksum anim) const;

		List<CRCChecksum> GetAnimationNames() const;
		List<CRCChecksum> GetBoneNames() const;
		
		bool GetAnimationMetadata(CRCChecksum anim, uint32_t &numFrames, uint32_t &numBones) const;

		const String& GetName() const;

		~AnimationBank();
		
		AnimationBank& operator=(const AnimationBank& other);


	private:

		zaa_ *p_AnimChunk = nullptr;
		class AnimDecompressor *p_Decompressor = nullptr;
	};
}