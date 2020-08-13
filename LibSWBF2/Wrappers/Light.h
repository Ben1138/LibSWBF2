#pragma once

#include "Chunks/LVL/common/SCOP.h"
#include "Chunks/LVL/common/DATA.h"
#include "InternalHelpers.h"

#include <stdint.h>
#include <string>


namespace LibSWBF2::Wrappers
{

using namespace LibSWBF2::Chunks::LVL::common;

struct Light {

public:

	glm::vec4 m_Position;
	glm::quat m_Rotation;

	glm::vec4 m_Color;

	String m_Name;
	ELightType m_Type;

	bool m_CastSpecular;

	Light(DATA* description, SCOP* body);
	Light() = default;
//	virtual std::string()=0;
};



struct OmnidirectionalLight : Light {

public:
	OmnidirectionalLight(DATA* description, SCOP* body);
//	virtual std::string GetInfo();
	int m_Radius;
};


struct SpotLight : Light {

public:
	SpotLight(DATA* description, SCOP* body);
//	virtual std::string GetInfo();
	int innerAngle, outerAngle;
};


struct DirectionalLight : Light {

public:
	DirectionalLight(DATA* description, SCOP* body);
//	virtual std::string GetInfo();
	int length;
};
 

}
