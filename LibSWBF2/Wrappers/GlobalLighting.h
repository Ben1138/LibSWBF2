#pragma once
#include "Chunks/LVL/lght/lght.h"
#include "Types/Colorf.h"
#include "Types/Vector4.h"
#include "Types/Vector3.h"


namespace LibSWBF2::Wrappers
{
	using namespace LibSWBF2::Chunks::LVL::lght;
	using namespace LibSWBF2::Types;

	class LIBSWBF2_API GlobalLightingConfig
	{
		friend class Level;

		GlobalLightingConfig(SCOP_LGHT* body);
		GlobalLightingConfig() = default;

		SCOP_LGHT* p_FieldsChunk;

	public:
		static bool FromChunk(SCOP_LGHT* body, GlobalLightingConfig& out);

		bool GetTopColor(Vector3& colorOut) const;
		bool GetBottomColor(Vector3& colorOut) const;

		bool GetLight1(String& light1NameOut) const;
		bool GetLight2(String& light2NameOut) const;

		String ToString() const;
	};
}