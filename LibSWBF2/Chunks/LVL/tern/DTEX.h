#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/LibString.h"
#include "Types/List.h"

namespace LibSWBF2::Chunks::LVL::terrain
{
	using Types::List;
	using Types::String;

	struct LIBSWBF2_API DTEX : public GenericChunk<"DTEX"_m>
	{
	public:
		List<String> m_LayerTextures;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}