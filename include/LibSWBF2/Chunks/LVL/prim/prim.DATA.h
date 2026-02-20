#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Chunks/RawData.h>
#include <LibSWBF2/Chunks/LVL/common/DATA.h>
#include <LibSWBF2/Types/Enums.h>


namespace LibSWBF2::Chunks::LVL::prim
{
	struct LIBSWBF2_API DATA_PRIM : public GenericChunk<"DATA"_m>
	{
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		Types::String ToString() const override;

		ECollisionPrimitiveType m_PrimitiveType;
		float m_Field1, m_Field2, m_Field3;
	};
}