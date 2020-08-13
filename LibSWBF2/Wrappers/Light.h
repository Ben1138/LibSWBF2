#pragma once

#include "Chunks/LVL/common/SCOP.h"
#include "Chunks/LVL/common/DATA.h"
#include "InternalHelpers.h"

#include "Types/Colorf.h"
#include "Types/Vector4.h"
#include "Types/Vector3.h"


#include <stdint.h>
#include <string>


namespace LibSWBF2::Wrappers
{

using namespace LibSWBF2::Chunks::LVL::common;
using namespace LibSWBF2::Types;

struct Light {

public:

	Vector3 m_Position;
	Vector4 m_Rotation;

	Colorf m_Color;

	String m_Name;
	ELightType m_Type;

	bool m_CastSpecular;

	Light(DATA* description, SCOP* body);
	Light() = default;

	virtual String ToString();
};



struct OmnidirectionalLight : Light {

public:
	OmnidirectionalLight(DATA* description, SCOP* body);
	int m_Radius;
};


struct SpotLight : Light {

public:
	SpotLight(DATA* description, SCOP* body);
	int m_InnerAngle, m_OuterAngle;
};


struct DirectionalLight : Light {

public:
	DirectionalLight(DATA* description, SCOP* body);
	int m_Length;
};
 

}
