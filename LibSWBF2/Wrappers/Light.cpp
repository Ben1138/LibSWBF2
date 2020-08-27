#include "stdafx.h"
#include "Light.h"
#include <stdint.h>


namespace LibSWBF2::Wrappers
{


bool Light::FromChunks(DATA_TAG *tag, SCOP_LGHT* body, Light*& out)
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

	switch (Light::TypeFromSCOP(body))
	{
		case ELightType::Omni:
            out = new OmnidirectionalLight(tag, body);
			break;
		case ELightType::Spot:
            out = new SpotLight(tag, body);
			break;
		case ELightType::Dir:
            out = new DirectionalLight(tag, body);
			break;
		default:
            LOG_ERROR("UNKNOWN LIGHT TYPE");
			return false;
			break;
	}

	return true;
}


ELightType Light::TypeFromSCOP(SCOP_LGHT *body)
{
	if (body -> GetChildren().Size() >= 3)
    {
	    DATA_LIGHTTYPE *typeChunk = dynamic_cast<DATA_LIGHTTYPE *>(body -> GetChildren()[2]); 
	   	return (ELightType) (.1f + typeChunk -> m_LightType);  
	}

	return ELightType::Unknown;
}


Light::Light(DATA_TAG* tag, SCOP_LGHT* body) : p_TagChunk(tag), p_FieldsChunk(body){}


Vector4 Light::GetRotation()
{
    return dynamic_cast<DATA_VEC4 *>(p_FieldsChunk -> p_DataFields[0]) -> m_Vec;
}

Vector3 Light::GetPosition()
{
    return dynamic_cast<DATA_VEC3 *>(p_FieldsChunk -> p_DataFields[1]) -> m_Vec;
}

Vector3 Light::GetColor()
{
    return dynamic_cast<DATA_VEC3 *>(p_FieldsChunk -> p_DataFields[3]) -> m_Vec;
}

String Light::GetName()
{
    return p_TagChunk -> m_Name;
}


String Light::ToString()
{
    return fmt::format(
            "Name: {}, Position: {}, Rotation: {}, Color: {}, ",
            GetName().Buffer(), GetPosition().ToString().Buffer(), 
            GetRotation().ToString().Buffer(), 
            GetColor().ToString().Buffer()
        ).c_str();
}

//ToString methods will be filled in with subclass specific fields when added...

String OmnidirectionalLight::ToString()
{
    return Light::ToString() + "Type: Omnidirectional";
}

OmnidirectionalLight::OmnidirectionalLight(DATA_TAG* tag, SCOP_LGHT* body) :
                    Light(tag, body) {}



String SpotLight::ToString()
{
    return Light::ToString() + "Type: Spot";
}

SpotLight::SpotLight(DATA_TAG* tag, SCOP_LGHT* body) :
                    Light(tag, body) {}



String DirectionalLight::ToString()
{
    return Light::ToString() + "Type: Directional";
}

DirectionalLight::DirectionalLight(DATA_TAG* tag, SCOP_LGHT* body) :
					Light(tag, body){}

}
