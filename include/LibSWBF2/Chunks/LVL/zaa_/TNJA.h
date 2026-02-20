#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>

namespace LibSWBF2::Chunks::LVL::animation
{
	struct LIBSWBF2_API TNJA : public GenericChunk<"TNJA"_m>
	{
	public:

		List<CRCChecksum> m_BoneCRCs;
		List<uint32_t>    m_RotationOffsets;
		List<uint32_t>    m_TranslationOffsets;
		List<float>     m_TranslationParams;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}