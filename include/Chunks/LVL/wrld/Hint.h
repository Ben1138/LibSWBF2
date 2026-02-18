#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"

#include "Chunks/LVL/common/PROP.h"



namespace LibSWBF2::Chunks::LVL::wrld
{
	struct XFRM;
	using common::PROP;


	struct LIBSWBF2_API Hint_TYPE : public GenericChunk<"TYPE"_m>
	{
		uint16_t m_Type;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;		
	};


	struct LIBSWBF2_API Hint_INFO : public GenericChunk<"INFO"_m>
	{
		Hint_TYPE * p_Type;
		STR<"NAME"_m> * p_Name;
		XFRM * p_Transform;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
		
		String ToString() const override;
	};


	struct LIBSWBF2_API Hint : public GenericChunk<"Hint"_m>
	{
		Hint_INFO* p_Info;

		List<PROP*> m_Properties;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}