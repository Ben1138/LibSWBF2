

#include <LibSWBF2/pch.h>
#include <LibSWBF2/Wrappers/CollisionPrimitive.h>
#include "InternalHelpers.h"
#include <stdint.h>


namespace LibSWBF2::Wrappers
{
    bool CollisionPrimitive::FromChunks(STR<"NAME"_m> *name, MASK *mask,
                           STR<"PRNT"_m> *parent, XFRM *transform,
                           DATA_PRIM *fields, CollisionPrimitive& out)
    {
        if (transform == nullptr || name == nullptr || fields == nullptr)
        {
            return false;
        }
        out = CollisionPrimitive(name, mask, parent, transform, fields);
        return true;
    }

    CollisionPrimitive::CollisionPrimitive(
                STR<"NAME"_m> *name, MASK *mask,
                STR<"PRNT"_m> *parent, XFRM *transform,
                DATA_PRIM *fields) : p_TransformChunk(transform),
                                     p_NameChunk(name), p_MaskChunk(mask),
                                     p_ParentChunk(parent), p_FieldsChunk(fields) {}


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

    String CollisionPrimitive::GetParentName() const
    {
        return p_ParentChunk -> ToString();
    }

    ECollisionPrimitiveType CollisionPrimitive::GetPrimitiveType() const
    {	
	    return p_FieldsChunk -> m_PrimitiveType;
    }

    ECollisionMaskFlags CollisionPrimitive::GetMaskFlags() const
    {
        return p_MaskChunk == nullptr ? ECollisionMaskFlags::All : p_MaskChunk -> m_MaskFlags;
    }
    
    bool CollisionPrimitive::GetCubeDims(float& xOut, float& yOut, float& zOut) const
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

    bool CollisionPrimitive::GetCylinderDims(float& radiusOut, float& heightOut) const 
    {
        bool status = p_FieldsChunk -> m_PrimitiveType == ECollisionPrimitiveType::Cylinder;
        if (status)
        {
            radiusOut = p_FieldsChunk -> m_Field1;
            heightOut = p_FieldsChunk -> m_Field2;
        }
        return status;

    }

    bool CollisionPrimitive::GetSphereRadius(float &radiusOut) const 
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


