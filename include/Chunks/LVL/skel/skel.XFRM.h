#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/Vector3.h"
#include "Types/Matrix3x3.h"

namespace LibSWBF2::Chunks::LVL::skel
{
	using Types::Vector3;
	using Types::Matrix3x3;

	struct LIBSWBF2_API XFRM : public GenericChunk<"XFRM"_m>
	{
	public:
		List<Matrix3x3> m_BoneRotations;
		List<Vector3> m_BonePositions;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}