#pragma once
#include "Chunks/GenericChunk.h"

namespace LibSWBF2::Chunks::LVL
{
	struct LIBSWBF2_API LVL : public GenericChunk<"ucfb"_m>
	{
	private:
		List<FNVHash> m_SubLVLsToLoad;
		bool m_IsSoundLVL = false;

		// only in Sound LVLs
		uint32_t m_NameHash;
		uint32_t m_SizeLeft;

	public:
		friend struct lvl_;

		static LVL* Create();
		static void Destroy(LVL* lvl);

		void ReadFromStream(FileReader& stream) override;

		// All sub LVLs not specified in here won't be loaded!
		bool ReadFromFile(String Path, const List<String>* subLVLsToLoad = nullptr);

		String ToString() override;

	protected:
		LVL() = default;
		~LVL() = default;
	};
}