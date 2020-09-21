

#include "stdafx.h"
#include "CollisionPrimitive.h"
#include "InternalHelpers.h"
#include <stdint.h>


namespace LibSWBF2::Wrappers
{
    static bool FromChunks(DATA_PRIM *fields, XFRM *transform, 
                            STR<"NAME"_m> *name, MASK *mask,
                            CollisionPrimitive& out)
    {
        if (transform == nullptr || name == nullptr || fields == nullptr)
        {
            return false;
        }
        out = CollisionPrimitive(fields, transform, name, mask);
        return true;
    }

    CollisionPrimitive::CollisionPrimitive(DATA_PRIM *fields, XFRM *transform, 
                                        STR<"NAME"_m> *name, MASK *mask) : p_FieldsChunk(fields), 
                                        p_TransformChunk(transform), p_NameChunk(name),
                                        p_MaskChunk(mask) {}


    Vector4 CollisionPrimitive::GetRotation() const
    {
        return MatrixToQuaternion(p_TransformChunk -> m_RotationMatrix);
    }

    Vector3 CollisionPrimitive::GetPosition() const
    {
        return p_TransformChunk -> m_Position;
    }

    String CollisionPrimitive::GetName() const
    {
        return p_NameChunk -> ToString();
    }

    ECollisionPrimitiveType CollisionPrimitive::GetPrimitiveType() const
    {	
	    return p_FieldsChunk -> m_PrimitiveType;
    }

    ECollisionMaskFlags CollisionPrimitive::GetMaskFlags() const
    {
        return p_MaskChunk == nullptr ? ECollisionMaskFlags::All : p_MaskChunk -> m_MaskFlags;
    }
    
    bool CollisionPrimitive::GetCubeDims(float_t& xOut, float_t& yOut, float_t& zOut) const
    {
        bool status = p_FieldsChunk -> m_PrimitiveType == ECollisionPrimitiveType::Cube;
        if (status)
        {
            xOut = p_FieldsChunk -> m_Field1;
            yOut = p_FieldsChunk -> m_Field2;
            zOut = p_FieldsChunk -> m_Field3;
        }
        return status;
    }

    bool CollisionPrimitive::GetCylinderDims(float_t& radiusOut, float_t& heightOut) const 
    {
        bool status = p_FieldsChunk -> m_PrimitiveType == ECollisionPrimitiveType::Cylinder;
        if (status)
        {
            radiusOut = p_FieldsChunk -> m_Field1;
            heightOut = p_FieldsChunk -> m_Field2;
        }
        return status;

    }

    bool CollisionPrimitive::GetSphereRadius(float_t &radiusOut) const 
    {
        bool status = p_FieldsChunk -> m_PrimitiveType == ECollisionPrimitiveType::Sphere;
        if (status)
        {
            radiusOut = p_FieldsChunk -> m_Field1;
        }
        return status;
    }

    String CollisionPrimitive::ToString() const
    {
        return p_FieldsChunk -> ToString();
    }
}


