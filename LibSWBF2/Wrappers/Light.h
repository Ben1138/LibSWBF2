#pragma once

#include "Chunks/LVL/lght/lght.h"
#include "InternalHelpers.h"

#include "Types/Colorf.h"
#include "Types/Vector4.h"
#include "Types/Vector3.h"


namespace LibSWBF2::Wrappers
{

using namespace LibSWBF2::Chunks::LVL::lght;
using namespace LibSWBF2::Types;

struct Light {

public:

	Vector4 GetRotation();
	Vector3 GetPosition();
	String GetName();
	Vector3 GetColor();

	Light(DATA_TAG* tag, SCOP_LGHT* body);
	Light() = default;

	virtual String ToString();
	static ELightType TypeFromSCOP(SCOP_LGHT* body);
	static bool FromChunks(DATA_TAG *tag, SCOP_LGHT* body, Light& out);


private:

	DATA_TAG* p_TagChunk;
	SCOP_LGHT* p_FieldsChunk;
};



struct OmnidirectionalLight : Light {

	OmnidirectionalLight(DATA_TAG* tag, SCOP_LGHT* body);
	String ToString();
	//int GetRadius();
};


struct SpotLight : Light {
	SpotLight(DATA_TAG* tag, SCOP_LGHT* body);
	String ToString();
	//void GetAngles(int& innerAngle, int& outerAngle);
};


struct DirectionalLight : Light {

public:
	DirectionalLight(DATA_TAG* tag, SCOP_LGHT* body);
	String ToString();
	//int GetLength();
};
 

}
