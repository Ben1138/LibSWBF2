#pragma once
#include "Chunks\GenericChunk.h"
#include "Types\Color.h"
#include "Types\Enums.h"

namespace LibSWBF2::Chunks::LVL::modl
{
	struct LIBSWBF2_EXP MTRL : public GenericChunk<"MTRL"_m>
	{
	public:
		EMaterialFlags m_Flags;
		Color m_DiffuseColor;
		Color m_SpecularColor;
		uint32_t m_SpecularExponent;
		uint32_t m_Unknown[2];
		String m_AttachedLight;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}