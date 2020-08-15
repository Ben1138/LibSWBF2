#include "Light.h"

#include <stdint.h>

void read3Floats(const uint8_t *rawPtr, 
				float_t& x, float_t& y,
				float_t& z){
    const float_t *floatPtr = reinterpret_cast<const float_t *>(rawPtr);
    x = *(floatPtr); 
    y = *(floatPtr + 1); 
    z = *(floatPtr + 2);   
}

void read4Floats(const uint8_t *rawPtr, 
				float_t& x, float_t& y,
                float_t& z, float_t& w){
    const float_t *floatPtr = reinterpret_cast<const float_t *>(rawPtr);
    x = *(floatPtr); 
    y = *(floatPtr + 1); 
    z = *(floatPtr + 2);
    w = *(floatPtr + 3);   
}


namespace LibSWBF2::Wrappers
{

bool Light::FromChunks(DATA *tag, SCOP* body, Light& out)
{
	if (tag == nullptr)
	{
		LOG_ERROR("Given light DATA  was NULL!");
		return false;
	}
	if (body == nullptr)
	{
		LOG_ERROR("Given light SCOP was NULL!");
		return false;
	}

	ELightType lightType = Light::TypeFromSCOP(body);

	switch (lightType)
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


ELightType Light::TypeFromSCOP(SCOP *body)
{
	if (body -> GetChildren().Size() >= 3){
		const uint8_t *rawData;
	    size_t size;

	    DATA *typeChunk = dynamic_cast<DATA *>(body -> GetChildren()[2]); 
	    typeChunk -> GetData(rawData, size);

	    if (size < 9){
	    	return ELightType::Unknown;
	    } else {
	   		return (ELightType) (.1f + *((const float_t *) (rawData + 5)));  
	   	}
	}

	return ELightType::Unknown;
}


Light::Light(DATA* tag, SCOP* body)
{
    m_CastSpecular = false;
    
    const uint8_t *rawData;
    const float_t *floatData;
    size_t size;


    //NAME (FIX MESSY)
    tag -> GetData(rawData, size);
    
    //Actual name always starts 17 bytes after header
    char *name = new char[size - 16]();
    memcpy(name, rawData + 17, size - 17);
    m_Name = name;
    delete[] name;


    /*
    Get DATA chunks for fields
    */

    const auto children = body -> GetChildren();
    float x,y,z,w;

    //ROTATION
    DATA *rotationChunk = dynamic_cast<DATA *>(children[0]); 
    rotationChunk -> GetData(rawData, size);

    read4Floats(rawData+5,x,y,z,w);
    m_Rotation = Vector4(x,y,z,w);
   
    //POSITION
    DATA *positionChunk = dynamic_cast<DATA *>(children[1]); 
    positionChunk -> GetData(rawData, size);

    read3Floats(rawData+5,x,y,z);  
    m_Position = Vector3(x,y,z);

    //COLOR
    DATA *colorChunk = dynamic_cast<DATA *>(children[3]); 
    colorChunk -> GetData(rawData, size);

    read3Floats(rawData+5,x,y,z); 
    m_Color = Vector3(x,y,z);
}

String Light::ToString()
{
    String posStr = m_Position.ToString();
    String rotStr = m_Rotation.ToString();
    String colStr = m_Color.ToString();

    return fmt::format(
            "Type: {}, Name: {}, Position: {}, Rotation: {}, Color: {}\n",
            ELightTypeToString(m_Type).Buffer(),
            m_Name.Buffer(), posStr.Buffer(), rotStr.Buffer(), 
            colStr.Buffer()).c_str();
}


OmnidirectionalLight::OmnidirectionalLight(DATA* description, SCOP* body) :
					Light(description, body) 
{
    int radius = 0;
    m_Type = ELightType::Omni;
}

String OmnidirectionalLight::ToString()
{
	String basicData = ELightTypeToString(m_Type) + " light " + Light::ToString();
	return basicData;
}

SpotLight::SpotLight(DATA* description, SCOP* body) :
					Light(description, body) 
{
    int innerAngle = 0;
    int outerAngle = 0;
    m_Type = ELightType::Spot;

}

DirectionalLight::DirectionalLight(DATA* description, SCOP* body) :
					Light(description, body)
{
	int length = 0;
	m_Type = ELightType::Dir;
}


}
