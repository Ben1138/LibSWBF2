#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/SoundBankHeader.h"

namespace LibSWBF2::Chunks::BNK
{
	using Types::SoundBankHeader;

	// Munged sound bank files.
	// These do not contain any sub chunks!
	struct LIBSWBF2_API BNK : public GenericChunk<"ucfb"_m>
	{
		static BNK* Create();
		static void Destroy(BNK* soundBank);

		SoundBankHeader m_SoundBank;

		void ReadFromStream(FileReader& stream) override;

		bool TryLookupName(String& result);
		String ToString() override;

	protected:
		BNK() = default;
		~BNK() = default;
	};
}