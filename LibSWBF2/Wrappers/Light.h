#pragma once
#include "Chunks/LVL/lght/lght.h"
#include "Types/Colorf.h"
#include "Types/Vector4.h"
#include "Types/Vector3.h"


namespace LibSWBF2::Wrappers
{
	using namespace LibSWBF2::Chunks::LVL::lght;
	using namespace LibSWBF2::Types;

	struct LIBSWBF2_API Light
	{
	public:
		String GetName();

		Vector4 GetRotation();
		Vector3 GetPosition();
		ELightType GetType();
		Vector3 GetColor();

		bool GetCastSpecular();
		bool GetRange(float_t& rangeOut);
		bool GetSpotAngles(float_t& innerAngleOut, float_t& outerAngleOut);

		Light(DATA_STRING* tag, SCOP_LGHT* body);
		Light() = default;

		String ToString();
		static bool FromChunks(DATA_STRING *tag, SCOP_LGHT* body, Light& out);

	private:
		DATA_STRING* p_TagChunk;
		SCOP_LGHT* p_FieldsChunk;
	};
}