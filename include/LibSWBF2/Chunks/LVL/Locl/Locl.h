#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Chunks/STR.h>
#include <LibSWBF2/Chunks/LVL/Locl/Locl.BODY.h>

namespace LibSWBF2::Chunks::LVL::Localization
{
	struct LIBSWBF2_API Locl : public GenericChunk<"Locl"_m>
	{
	public:
		STR<"NAME"_m>* p_Name;
		BODY* p_Body;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}