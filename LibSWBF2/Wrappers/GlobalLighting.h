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

struct GlobalLightingConfig {

public:

	bool GetTopColor(Vector3& colorOut);
	bool GetBottomColor(Vector3& colorOut);

	bool GetLight1(String& light1NameOut);
	bool GetLight2(String& light2NameOut);

	GlobalLightingConfig(SCOP_LGHT* body);
	GlobalLightingConfig() = default;

	String ToString();
	static bool FromChunk(SCOP_LGHT* body, GlobalLightingConfig& out);


private:
	SCOP_LGHT* p_FieldsChunk;
};

}

