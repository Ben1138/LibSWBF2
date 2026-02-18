#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/Matrix3x3.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
	using Types::Matrix3x3;

	struct LIBSWBF2_API XFRM : public GenericChunk<"XFRM"_m>
	{
	public:
		Matrix3x3 m_RotationMatrix;
		Vector3 m_Position;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}