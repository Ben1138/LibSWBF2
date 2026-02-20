#pragma once
#include <LibSWBF2/Chunks/LVL/prim/prim.h>
#include <LibSWBF2/Chunks/LVL/prim/prim.DATA.h>
#include <LibSWBF2/Chunks/LVL/prim/MASK.h>
#include <LibSWBF2/Chunks/LVL/wrld/XFRM.h>
#include <LibSWBF2/Chunks/STR.h>

#include <LibSWBF2/Types/Vector4.h>
#include <LibSWBF2/Types/Vector3.h>
#include <LibSWBF2/Types/Matrix3x3.h>


namespace LibSWBF2::Wrappers
{
	using namespace LibSWBF2::Chunks::LVL::prim;
	using namespace LibSWBF2::Chunks::LVL::wrld;
	using namespace LibSWBF2::Types;
	using namespace LibSWBF2::Chunks;

	class LIBSWBF2_API CollisionPrimitive
	{
		friend class Level;
		friend class List<CollisionPrimitive>;

	private:
		
		DATA_PRIM *p_FieldsChunk;
		XFRM *p_TransformChunk;
		STR<"NAME"_m> *p_NameChunk;
		MASK *p_MaskChunk;
		STR<"PRNT"_m> *p_ParentChunk;
		
		CollisionPrimitive(STR<"NAME"_m> *name, MASK *mask,
                           STR<"PRNT"_m> *parent, XFRM *transform,
                           DATA_PRIM *fields);

		CollisionPrimitive() = default;

		
		static bool FromChunks(STR<"NAME"_m> *name, MASK *mask,
                           STR<"PRNT"_m> *parent, XFRM *transform,
                           DATA_PRIM *fields, CollisionPrimitive& out);
	public:
		
		String GetName() const;
		String GetParentName() const;

		Vector4 GetRotation() const;
		Vector3 GetPosition() const;

		ECollisionPrimitiveType GetPrimitiveType() const;
		ECollisionMaskFlags GetMaskFlags() const;

		bool GetCubeDims(float& xOut, float& yOut, float& zOut) const;
		bool GetCylinderDims(float& radiusOut, float& heightOut) const;
		bool GetSphereRadius(float &radiusOut) const;
		
		String ToString() const;
	};
}