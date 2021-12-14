#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/Color4u8.h"
#include "Types/Enums.h"

namespace LibSWBF2::Chunks::LVL::modl
{
	struct LIBSWBF2_API MTRL : public GenericChunk<"MTRL"_m>
	{
	public:
		EMaterialFlags m_Flags;
		Color4u8 m_DiffuseColor;
		Color4u8 m_SpecularColor;
		uint32_t m_SpecularExponent;
		uint32_t m_Parameters[2];
		String m_AttachedLight;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}