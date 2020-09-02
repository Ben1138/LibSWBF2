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

	String GetName();

	Vector4 GetRotation();
	Vector3 GetPosition();
	ELightType GetType();
	Vector3 GetColor();

	bool GetCastSpecular();


	/*Type specific getters*/
	bool GetOmniRadius(float_t& radiusOut);

	bool GetSpotAngles(float_t& innerAngleOut, float_t& outerAngleOut);

	bool GetDirLength(float_t& lengthOut);
	bool GetDirTexture(String& textureNameOut);


	Light(DATA_TAG* tag, SCOP_LGHT* body);
	Light() = default;

	String ToString();
	static bool FromChunks(DATA_TAG *tag, SCOP_LGHT* body, Light& out);


private:

	DATA_TAG* p_TagChunk;
	SCOP_LGHT* p_FieldsChunk;
};

}