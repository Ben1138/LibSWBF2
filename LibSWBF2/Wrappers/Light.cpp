#include "Light.h"

#include <string>
#include <iostream>
#define COUT(x) std::cout << x << std::endl


void read3Floats(const uint8_t *rawPtr,
                            float_t& x,
                            float_t& y,
                            float_t& z){
    const float_t *floatPtr = reinterpret_cast<const float_t *>(rawPtr);
    x = *(floatPtr); 
    y = *(floatPtr + 1); 
    z = *(floatPtr + 2);   
}


void read4Floats(const uint8_t *rawPtr,
                            float_t& x,
                            float_t& y,
                            float_t& z,
                            float_t& w){
    const float_t *floatPtr = reinterpret_cast<const float_t *>(rawPtr);
    x = *(floatPtr); 
    y = *(floatPtr + 1); 
    z = *(floatPtr + 2);
    w = *(floatPtr + 3);   
}




namespace LibSWBF2::Wrappers
{



Light::Light(DATA* description, SCOP* body)
{

    LOG_WARN("CONSTRUCTING NEW LIGHT");

    m_CastSpecular = false;
    
    /*
    NAME (FIX MESSY)
    */

    const uint8_t *rawData;
    const float_t *floatData;
    size_t size;
    description -> GetData(rawData, size);
    
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
    m_Color = Colorf(x,y,z);
}

String Light::ToString()
{

    String posStr = m_Position.ToString();
    String rotStr = m_Rotation.ToString();
    String colStr = m_Color.ToString();

    return fmt::format(
            "Name: {}, Position: {}, Rotation: {}, Color: {}",
            m_Name.Buffer(), posStr.Buffer(), rotStr.Buffer(), 
            colStr.Buffer()).c_str();
}


OmnidirectionalLight::OmnidirectionalLight(DATA* description, SCOP* body) :
					Light(description, body) 
{
    int radius = 0;
}

SpotLight::SpotLight(DATA* description, SCOP* body) :
					Light(description, body) 
{
    int innerAngle = 0;
    int outerAngle = 0;
}

DirectionalLight::DirectionalLight(DATA* description, SCOP* body) :
					Light(description, body)
{
	int length = 0;
}


}
