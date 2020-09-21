#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/RawData.h"
#include "prim.h"
#include "Types/Enums.h"


namespace LibSWBF2::Chunks::LVL::prim
{
	struct LIBSWBF2_API DATA_PRIM : public DATA
	{

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;

		uint32_t m_PrimitiveType;
		float_t m_Field1, m_Field2, m_Field3;
	};
}