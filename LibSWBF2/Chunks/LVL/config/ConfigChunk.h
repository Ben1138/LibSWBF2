#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
#include "config.NAME.h"

namespace LibSWBF2::Chunks::LVL::config
{
	template<uint32_t Header>
	struct LIBSWBF2_API ConfigChunk : public GenericChunk<Header>
	{
	public:
		config_NAME *p_Hash = nullptr;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};

	struct LIBSWBF2_API lght : public ConfigChunk<"lght"_m> {};
	struct LIBSWBF2_API fx__ : public ConfigChunk<"fx__"_m> {};
	struct LIBSWBF2_API sky_ : public ConfigChunk<"sky_"_m> {};
 	struct LIBSWBF2_API bnd_ : public ConfigChunk<"bnd_"_m> {};
	struct LIBSWBF2_API prp_ : public ConfigChunk<"prp_"_m> {};
}
