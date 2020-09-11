#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/List.h"
#include "Types/LocalizeEntry.h"

namespace LibSWBF2::Chunks::LVL::Localization
{
	using Types::List;
	using Types::LocalizeEntry;

	struct LIBSWBF2_API BODY : public GenericChunk<"BODY"_m>
	{
		List<LocalizeEntry> m_LocalizeEntries;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}