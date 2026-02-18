#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/LibString.h"

namespace LibSWBF2::Chunks
{
	template<uint32_t Header>
	struct LIBSWBF2_API STRMULT : public GenericChunk<Header>
	{
	public:
		List<String> m_Texts;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}