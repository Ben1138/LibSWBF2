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

	if (!tag -> m_Local)
	{
        LOG_WARN("Global light configurations not yet supported");
		return false;
	}

	switch (Light::TypeFromSCOP(body))
	{
		case ELightType::Omni:
            out = OmnidirectionalLight(tag, body);
			break;
		case ELightType::Spot:
            out = SpotLight(tag, body);
			break;
		case ELightType::Dir:
            out = DirectionalLight(tag, body);
			break;
		default:
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
	   	return (ELightType) (.1f + typeChunk -> m_LightType;);  
	}

	return ELightType::Unknown;
}


Light::Light(DATA_TAG* tag, SCOP_LGHT* body) : p_TagChunk(tag), p_DataFields(body){}

String Light::ToString()
{
    String posStr = GetPosition().ToString();
    String rotStr = GetRotation().ToString();
    String colStr = GetColor().ToString();

    return fmt::format(
            "Name: {}, Position: {}, Rotation: {}, Color: {}\n",
            GetName().Buffer(), posStr.Buffer(), rotStr.Buffer(), 
            colStr.Buffer());
}

//ToString methods will be filled in with subclass specific fields when added...


OmnidirectionalLight::OmnidirectionalLight(DATA_TAG* description, SCOP_LGHT* body) :
					Light(description, body) {}

String OmnidirectionalLight::ToString()
{
	return "Type: Omnidirectional, " + Light::ToString();
}



String SpotLight::ToString()
{
    return "Type: Spot, " + Light::ToString();
}

SpotLight::SpotLight(DATA_TAG* tag, SCOP_LGHT* body) :
                    Light(tag, body) {}



String DirectionalLight::ToString()
{
    return "Type: Directional, " + Light::ToString();
}

DirectionalLight::DirectionalLight(DATA_TAG* description, SCOP_LGHT* body) :
					Light(description, body){}

}
