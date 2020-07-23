#pragma once
#include "Chunks/GenericChunk.h"

namespace LibSWBF2::Chunks::LVL
{
	struct LIBSWBF2_API LVL : public GenericChunk<"ucfb"_m>
	{
	private:
		List<FNVHash> m_SubLVLsToLoad;

	public:
		friend struct lvl_;

		static LVL* Create();
		static void Destroy(LVL* lvl);

		using BaseChunk::ReadFromFile;

		// All sub LVLs not specified in here won't be loaded!
		bool ReadFromFile(const String& Path, const List<String>& subLVLsToLoad);

	protected:
		LVL() = default;
		~LVL() = default;
	};
}