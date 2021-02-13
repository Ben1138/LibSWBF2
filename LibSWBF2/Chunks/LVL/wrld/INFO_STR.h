#pragma once
#include "Chunks/GenericChunk.h"


namespace LibSWBF2::Chunks::LVL::wrld
{
	struct LIBSWBF2_API anim_INFO : public GenericChunk<"INFO"_m>
	{
	public:
		String m_Name;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}