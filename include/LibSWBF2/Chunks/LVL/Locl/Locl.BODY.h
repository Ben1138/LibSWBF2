#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Types/List.h>
#include <LibSWBF2/Types/LocalizeEntry.h>

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

		String ToString() const override;
	};
}