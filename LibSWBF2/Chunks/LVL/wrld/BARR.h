#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"


namespace LibSWBF2::Chunks::LVL::wrld
{
	struct XFRM;
	struct SIZE;

	struct LIBSWBF2_API BARR_FLAG : public GenericChunk<"FLAG"_m>
	{
		uint32_t m_Flag;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;		
	};


	struct LIBSWBF2_API BARR_INFO : public GenericChunk<"INFO"_m>
	{
		STR<"NAME"_m> * p_Name;
		XFRM * p_Transform;
		SIZE * p_Size;

		BARR_FLAG * p_Flag;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
		
		String ToString() const override;
	};


	struct LIBSWBF2_API BARR : public GenericChunk<"BARR"_m>
	{
		BARR_INFO* p_Info;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}