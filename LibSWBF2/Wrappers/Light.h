#pragma once

#include "Chunks/LVL/common/SCOP.h"
#include "Chunks/LVL/common/DATA.h"
#include "InternalHelpers.h"


#include <stdint.h>


typedef enum {
	
    OMNI,
	OMNI_CAST_SPEC,
	DIR,
	DIR_CAST_SPEC,
	SPOT,
	SPOT_CAST_SPEC,


	FORCE_UINT32 = (uint32_t) 0xffffffff,
} LIGHTTYPE;


using namespace LibSWBF2::Chunks::LVL::common;

struct BaseLight {

public:

	glm::vec4 position;
	glm::quat rotation;

	glm::vec4 color;

	std::string name;
	LIGHTTYPE type;

	bool cast_specular;

	BaseLight(DATA& description, SCOP& body);
};



struct OmnidirectionalLight : BaseLight {

public:
	OmnidirectionalLight(DATA& description, SCOP& body);
	int radius;
};



struct SpotLight : BaseLight {

public:
	SpotLight(DATA& description, SCOP& body);
	int innerAngle, outerAngle;
};



struct DirectionalLight : BaseLight {

public:
	DirectionalLight(DATA& description, SCOP& body);
	int length;
};
