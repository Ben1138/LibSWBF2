#pragma once
#include "GenericChunk.h"

namespace LibSWBF2::Chunks
{
	template<uint32_t Header>
	struct LIBSWBF2_API STR : public GenericChunk<Header>
	{
		String m_Text;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;

	private:
		inline bool IsValidStringChar(char c);
	};
}