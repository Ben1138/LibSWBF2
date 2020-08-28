#include "stdafx.h"
#include "Light.h"
#include <stdint.h>


namespace LibSWBF2::Wrappers
{


bool Light::FromChunks(DATA_TAG *tag, SCOP_LGHT* body, Light& out)
{
    if (body == nullptr || tag == nullptr)
    {
        LOG_ERROR("tag or body was null in Light wrapper constructor");
        return false;
    }

	if (!tag -> m_LocalLight)
	{
        LOG_WARN("Global light configurations not yet supported");
		return false;
	}

	out = Light(tag, body);
	return true;
}


Light::Light(DATA_TAG* tag, SCOP_LGHT* body) : p_TagChunk(tag), p_FieldsChunk(body){}


Vector4 Light::GetRotation()
{
    return p_FieldsChunk -> p_RotationChunk -> m_Vec;
}

Vector3 Light::GetPosition()
{
    return p_FieldsChunk -> p_PositionChunk -> m_Vec;
}

Vector3 Light::GetColor()
{
    return p_FieldsChunk -> p_ColorChunk -> m_Vec;
}

String Light::GetName()
{
    return p_TagChunk -> m_Name;
}

ELightType Light::GetType()
{	
	auto* typeChunk = p_FieldsChunk -> p_TypeChunk;

	if (typeChunk != nullptr)
    {
	   	return (ELightType) (.1f + typeChunk -> m_LightType);  
	}

	return ELightType::Unknown;
}

String Light::ToString()
{
    return fmt::format(
            "Name: {}, Position: {}, Rotation: {}, Color: {}, Type: {}",
            GetName().Buffer(), GetPosition().ToString().Buffer(), 
            GetRotation().ToString().Buffer(), GetColor().ToString().Buffer(),
            ELightTypeToString(GetType()).Buffer()
        ).c_str();
}


}