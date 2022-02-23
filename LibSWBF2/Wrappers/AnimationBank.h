#pragma once
#include "Types/Enums.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	struct zaa_;
}

namespace LibSWBF2::Wrappers
{
	using Types::List;
	using Types::String;


	class LIBSWBF2_API AnimationBank
	{
	typedef LibSWBF2::Chunks::LVL::animation::zaa_ zaa_ ;


		friend List<AnimationBank>;

	public:

		static bool FromChunk(zaa_ *chunk, AnimationBank &setOut);

		bool GetCurve(CRCChecksum anim, CRCChecksum bone, uint16_t component,
					List<uint16_t> &frame_indices, List<float_t> &frame_values) const;
	
		bool ContainsAnimation(CRCChecksum anim) const;

		List<CRCChecksum> GetAnimations() const;
		List<CRCChecksum> GetBones(CRCChecksum anim) const;
		
		bool GetAnimationMetadata(CRCChecksum anim, uint32_t &numFrames, uint32_t &numBones) const;

		const String& GetName() const;

		~AnimationBank();

		AnimationBank& operator=(const AnimationBank& other);


	private:

		zaa_ *p_AnimChunk = nullptr;
		class AnimDecompressor *p_Decompressor = nullptr;
	};
}