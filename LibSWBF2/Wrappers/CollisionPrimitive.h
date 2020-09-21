#pragma once
#include "Chunks/LVL/coll/coll.h"
#include "Chunks/LVL/prim/prim.h"
#include "Types/Vector4.h"
#include "Types/Vector3.h"
#include "Types/Quaternion.h"


namespace LibSWBF2::Wrappers
{
	using namespace LibSWBF2::Chunks::LVL::coll;
	using namespace LibSWBF2::Chunks::LVL::prim;
	using namespace LibSWBF2::Types;

	class LIBSWBF2_API CollisionPrimitive
	{
		friend class Level;
		friend class List<CollisionPrimitive>;

		CollisionPrimitive() = default;
		CollisionPrimitive()

	private:
		DATA_PRIM *p_FieldsChunk;
		XFRM *p_TransformChunk;
		STR<"NAME"_m> p_NameChunk;
		MASK *p_MaskChunk;

	public:
		static bool FromChunks(DATA_PRIM *fields, XFRM *transform, 
							STR<"NAME"_m> *name, MASK *mask,
							CollisionPrimitive& out);

		String GetName() const;

		Vector4 GetRotation() const;
		Vector3 GetPosition() const;

		ECollisionPrimitiveType GetType() const;

		bool GetCubeDims(float_t& xOut, float_t& yOut, float_t& zOut) const;
		bool GetCylinderDims(float_t& radiusOut, float_t& heightOut) const;
		bool GetSphereRadius(float_t &radiusOut) const;
		
		String ToString() const;
	};
}