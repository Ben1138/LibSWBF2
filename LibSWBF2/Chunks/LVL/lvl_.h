#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
#include "Types/SoundBankHeader.h"
#include "Types/Enums.h"

namespace LibSWBF2::Chunks::LVL
{
	using Types::SoundBankHeader;

	struct LIBSWBF2_API lvl_ : public GenericChunk<"lvl_"_m>
	{
	public:
		uint32_t m_NameHash = 0;
		uint32_t m_SizeLeft = 0;
		ELVLType m_LVLType;

		// optional, sound LVLs only
		SoundBankHeader m_SoundBankHeader;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		bool TryLookupName(String& result);
		String ToString() const override;

	private:
		inline void ReadContents(FileReader& stream);
	};
}