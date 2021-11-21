#pragma once
#include "Chunks/GenericChunk.h"


namespace LibSWBF2::Chunks::LVL::wrld
{
	struct LIBSWBF2_API anim_INFO : public GenericChunk<"INFO"_m>
	{
	public:

		String m_Name;
		
		float m_RunTime;
		uint8_t m_Looping;
		uint8_t m_LocalTranslation;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
		
		String ToString() const override;
	};
}