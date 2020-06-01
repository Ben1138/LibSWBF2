#pragma once
#include "GenericChunk.h"

namespace LibSWBF2::Chunks
{
	template<uint32_t Header>
	struct LIBSWBF2_EXP STR : public GenericChunk<Header>
	{
		STR() = default;
		~STR() = default;

	public:
		String m_Text;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}