#pragma once
#include "Chunks/GenericChunk.h"

namespace LibSWBF2::Chunks::LVL::common
{
	struct LIBSWBF2_API PROP : public GenericChunk<"PROP"_m>
	{
	public:
		FNVHash m_PropertyName;
		String m_Value;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}
