#pragma once

#include "Chunks/LVL/common/SCOP.h"
#include "Chunks/LVL/common/DATA.h"
#include "InternalHelpers.h"

#include "Types/Colorf.h"
#include "Types/Vector4.h"
#include "Types/Vector3.h"


namespace LibSWBF2::Wrappers
{

using namespace LibSWBF2::Chunks::LVL::common;
using namespace LibSWBF2::Types;

struct Light {

public:

	Vector3 GetPosition();
	Vector4 GetRotation();

	bool m_CastSpecular;

	Light(DATA* tag, SCOP* body);
	Light() = default;

	virtual String ToString();
	static ELightType TypeFromSCOP(SCOP* body);
	static bool FromChunks(DATA *tag, SCOP* body, Light& out);
};



struct OmnidirectionalLight : Light {

public:
	OmnidirectionalLight(DATA* description, SCOP* body);
	int m_Radius;
	String ToString();
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
