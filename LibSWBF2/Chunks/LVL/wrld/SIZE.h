#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/List.h"

namespace LibSWBF2::Chunks::LVL::wrld
{
	struct LIBSWBF2_API SIZE : public GenericChunk<"SIZE"_m>
	{
	public:
		Vector3 m_Dimensions;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}