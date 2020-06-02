#pragma once
#include "Chunks\BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MODL;

	enum class ECollisionPrimitive : uint32_t
	{
		None = 0xffffffff,
		Sphere1 = 0,	// 0 and 1 are both spheres
		Sphere2 = 1,
		Cylinder = 2,
		Cube = 4
	};

	struct LIBSWBF2_EXP SWCI : public BaseChunk
	{
		SWCI() = default;
		~SWCI() = default;

		ECollisionPrimitive m_PrimitiveType = ECollisionPrimitive::None;

		// Sphere
		//	x: radius
		// Cylinder
		//	x: radius
		//	y: height
		// Cube
		//	x: width
		//	y: height
		//	z: depth
		Vector3 m_Dimensions;

	protected:
		friend MODL;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}
