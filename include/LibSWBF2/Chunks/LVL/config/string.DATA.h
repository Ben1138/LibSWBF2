#pragma once
#include <LibSWBF2/Chunks/LVL/config/DATA.h>
#include <LibSWBF2/Types/Enums.h>


namespace LibSWBF2::Chunks::LVL::config
{
	struct LIBSWBF2_API DATA_STRING : public DATA_CONFIG
	{
		uint32_t m_Tag;
		String m_String;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}
