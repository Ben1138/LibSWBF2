#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
#include "PROP.h"

namespace LibSWBF2::Chunks::LVL::common
{
	template<uint32_t Header>
	struct LIBSWBF2_API GenericClass : public GenericChunk<Header>
	{
	public:
		STR<"BASE"_m>* p_Base;
		STR<"TYPE"_m>* p_Type;

		List<PROP*> m_Properties;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};

	struct LIBSWBF2_API GenericClassNC : public GenericClass<0> {};
	struct LIBSWBF2_API entc : public GenericClass<"entc"_m> {};
	struct LIBSWBF2_API ordc : public GenericClass<"ordc"_m> {};
	struct LIBSWBF2_API wpnc : public GenericClass<"wpnc"_m> {};
	struct LIBSWBF2_API expc : public GenericClass<"expc"_m> {};
} 