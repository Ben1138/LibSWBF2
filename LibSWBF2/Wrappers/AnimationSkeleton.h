#pragma once
#include "req.h"
#include "Types/Vector3.h"
#include "Types/Vector4.h"
#include "Types/List.h"
#include "Types/LibString.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	struct zaf_;
}

namespace LibSWBF2::Wrappers
{
	using Types::List;
	using Types::Vector3;
	using Types::Vector4;
	using Types::String;


	#pragma pack(push,1)
	struct LIBSWBF2_API Joint
	{
		uint32_t m_BoneName;
		Types::Vector4 m_Rotation;
		Types::Vector3 m_Position;
		uint32_t m_ParentBoneName;
		// Might include the other 2 crcs if necessary
	};
	#pragma pack(pop)

	struct Level;

	class LIBSWBF2_API AnimationSkeleton
	{
	typedef LibSWBF2::Chunks::LVL::animation::zaf_ zaf_ ;


		friend Types::List<AnimationSkeleton>;


	private:
		friend Level;

		AnimationSkeleton() = default;
		~AnimationSkeleton() = default;

		zaf_* p_AnimSkeleton;

	public:
		static bool FromChunk(zaf_* animSkelChunk, AnimationSkeleton& out);

		const String& GetName() const;
		bool GetJoints(Types::List<Joint>& joints) const;
	};
}