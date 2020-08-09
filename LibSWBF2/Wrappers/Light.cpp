#include "Light.h"


BaseLight::BaseLight(DATA& description, SCOP& body){

	name = //description getString
	type = body.GetDataSize();

	float body.getChild(0).

}



OmnidirectionalLight::OmnidirectionalLight(DATA& description, SCOP& body) :
					BaseLight(description, body) {

//int radius;
}




SpotLight::SpotLight(DATA& description, SCOP& body) :
					BaseLight(description, body) {


//int innerAngle, outerAngle;
}



DirectionalLight::DirectionalLight(DATA& description, SCOP& body) :
					BaseLight(description, body) {

	//int length;
}

