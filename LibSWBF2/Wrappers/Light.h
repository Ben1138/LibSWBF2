#pragma once

#include "Chunks/LVL/common/SCOP.h"
#include "Chunks/LVL/common/DATA.h"
#include "InternalHelpers.h"

#include <stdint.h>
#include <string>


namespace LibSWBF2::Wrappers
{

typedef enum {
	
    OMNI,
	OMNI_CAST_SPEC,
	DIR,
	DIR_CAST_SPEC,
	SPOT,
	SPOT_CAST_SPEC,


	FORCE_UINT32 = (uint32_t) 0xffffffff,
} LIGHTTYPE;


using LibSWBF2::Chunks::LVL::common;

struct Light {

public:

	glm::vec4 m_Position;
	glm::quat m_Rotation;

	glm::vec4 m_Color;

	std::string m_Name;
	LIGHTTYPE m_Type;

	bool m_CastSpecular;

	Light(DATA description, SCOP body);
	virtual std::string GetInfo()=0;
};



struct OmnidirectionalLight : Light {

public:
	OmnidirectionalLight(DATA description, SCOP body);
	virtual std::string GetInfo();
	int m_Radius;
};


struct SpotLight : Light {

public:
	SpotLight(DATA description, SCOP body);
	virtual std::string GetInfo();
	int innerAngle, outerAngle;
};


struct DirectionalLight : Light {

public:
	DirectionalLight(DATA description, SCOP body);
	virtual std::string GetInfo();
	int length;
};
 

}
