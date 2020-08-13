#include "Light.h"

#include <string>
#include <iostream>
#define COUT(x) std::cout << x << std::endl


namespace LibSWBF2::Wrappers
{

using namespace LibSWBF2::Chunks::LVL::common;


Light::Light(DATA& description, SCOP& body){
    
    const uint8_t *nameStr;
    size_t size;
    description.GetData(nameStr, size);
    
    m_Name = std::string(reinterpret_cast<const char *>(nameStr), size);
    
    const auto children = body.GetChildren();
    
    COUT(m_Name);
}



OmnidirectionalLight::OmnidirectionalLight(DATA& description, SCOP& body) :
					Light(description, body) {
    int radius = 0;
}


SpotLight::SpotLight(DATA& description, SCOP& body) :
					Light(description, body) {
    int innerAngle = 0;
    int outerAngle = 0;
}


DirectionalLight::DirectionalLight(DATA& description, SCOP& body) :
					Light(description, body) {
	int length = 0;
}


}
