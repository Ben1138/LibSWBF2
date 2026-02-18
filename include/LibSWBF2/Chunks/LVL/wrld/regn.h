#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Types/List.h>
#include <LibSWBF2/Chunks/LVL/common/PROP.h>
#include <LibSWBF2/Chunks/LVL/wrld/wrld.INFO.h>

namespace LibSWBF2::Chunks::LVL::wrld
{
	using LibSWBF2::Chunks::LVL::wrld::INFO;
	using common::PROP;

	struct LIBSWBF2_API regn : public GenericChunk<"regn"_m>
	{
	public:
		INFO* p_Info;
		List<PROP*> m_Props;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}