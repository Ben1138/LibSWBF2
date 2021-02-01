/*

#pragma once

#include "Chunks/LVL/config/ConigClass.h"
#include "Types/Color4.h"
#include "Types/Vector4.h"
#include "Types/Vector3.h"


namespace LibSWBF2::Wrappers
{
	using namespace LibSWBF2::Chunks::LVL::lght;
	using namespace LibSWBF2::Types;

	class LIBSWBF2_API Light
	{
		friend class Level;
		friend class List<Light>;

		Light(DATA_STRING* tag, SCOP_LGHT* body);
		Light() = default;

		DATA_STRING* p_TagChunk;
		SCOP_LGHT* p_FieldsChunk;

	public:
		static bool FromChunks(DATA_STRING *tag, SCOP_LGHT* body, Light& out);

		const String& GetName() const;

		Vector4 GetRotation() const;
		Vector3 GetPosition() const;
		ELightType GetType() const;
		Vector3 GetColor() const;

		bool GetRange(float_t& rangeOut) const;
		bool GetSpotAngles(float_t& innerAngleOut, float_t& outerAngleOut) const;

		String ToString() const;

		FNVHash m_WorldName;
	};
}


*/
