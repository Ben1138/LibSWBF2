#include "Light.h"

#include <string>
#include <iostream>
#define COUT(x) std::cout << x << std::endl


namespace LibSWBF2::Wrappers
{


Light::Light(DATA description, SCOP body){
    
    const uint8_t *rawData;
    size_t size;
    description.GetData(rawData, size);
    
    char *name = new char[size - 5];
    memcpy(name, rawData + 5, size - 5);
    name[size - 6] = 0;
    
    m_Name = name;
    
    //const auto children = body.GetChildren();
    
    COUT(name);
}



OmnidirectionalLight::OmnidirectionalLight(DATA description, SCOP body) :
					Light(description, body) {
    int radius = 0;
}


SpotLight::SpotLight(DATA description, SCOP body) :
					Light(description, body) {
    int innerAngle = 0;
    int outerAngle = 0;
}


DirectionalLight::DirectionalLight(DATA description, SCOP body) :
					Light(description, body) {
	int length = 0;
}


}
