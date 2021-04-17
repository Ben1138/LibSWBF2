#pragma once
#include "Types/Enums.h"
#include "Types/Curve.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	struct zaa_;
}

namespace LibSWBF2::Wrappers
{
	using Types::List;
	using Types::String;
	using Types::Curve;


	class LIBSWBF2_API AnimationBank
	{
	typedef LibSWBF2::Chunks::LVL::animation::zaa_ zaa_ ;


		friend List<AnimationBank>;

	public:

		static bool FromChunk(zaa_ *chunk, AnimationBank &setOut);

		bool GetCurve(CRCChecksum anim, CRCChecksum bone, uint16_t component,
					List<uint16_t> &frame_indices, List<float_t> &frame_values) const;

		// Throws exception if <anim> isnt in the bank,
		// or <bone> is not among <anim>'s bones, or if
		// an error occurs during the decompression process.
		Curve<uint16_t> GetCurve(CRCChecksum anim, CRCChecksum bone, ECurveType component) const;
	
		bool ContainsAnimation(CRCChecksum anim) const;

		List<CRCChecksum> GetAnimations() const;
		List<CRCChecksum> GetBones() const;
		
		bool GetAnimationMetadata(CRCChecksum anim, uint32_t &numFrames, uint32_t &numBones) const;

		const String& GetName() const;

		~AnimationBank();

		AnimationBank& operator=(const AnimationBank& other);


	private:

		zaa_ *p_AnimChunk = nullptr;
		class AnimDecompressor *p_Decompressor = nullptr;
	};
}