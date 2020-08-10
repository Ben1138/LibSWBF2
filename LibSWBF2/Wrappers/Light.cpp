#include "Light.h"

#include <string>
#include <iostream>

#define COUT(x) std::cout << x << std::endl

namespace LibSWBF2::Wrappers
{

using namespace LibSWBF2::Chunks::LVL::common;

BaseLight::BaseLight(DATA& description, SCOP& body){
    
    const uint8_t *nameStr;
    size_t size;
    description.GetData(nameStr, size);
    
    name = std::string(reinterpret_cast<const char *>(nameStr), size);
    
    const auto children = body.GetChildren();
    
    COUT(name);
}



OmnidirectionalLight::OmnidirectionalLight(DATA& description, SCOP& body) :
					BaseLight(description, body) {

//int radius;
}



/*
SpotLight::SpotLight(DATA& description, SCOP& body) :
					BaseLight(description, body) {


//int innerAngle, outerAngle;
}



DirectionalLight::DirectionalLight(DATA& description, SCOP& body) :
					BaseLight(description, body) {

	//int length;
}

*/

}
