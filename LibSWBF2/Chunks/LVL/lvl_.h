#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
#include "Types/SoundBankHeader.h"

namespace LibSWBF2::Chunks::LVL
{
	using Types::SoundBankHeader;

	struct LIBSWBF2_API lvl_ : public GenericChunk<"lvl_"_m>
	{
	public:
		uint32_t m_NameHash = 0;
		uint32_t m_SizeLeft = 0;
		bool m_IsSoundLVL = false;

		// optional, sound LVLs only
		SoundBankHeader m_SoundBankHeader;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		bool TryLookupName(String& result);
		String ToString() override;

	private:
		inline void ReadContents(FileReader& stream);
	};
}