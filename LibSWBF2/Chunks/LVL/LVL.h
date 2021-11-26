#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/Enums.h"

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

		void ReadFromStream(FileReader& stream) override;

		// All sub LVLs not specified in here won't be loaded!
		bool ReadFromFile(String Path, const List<String>* subLVLsToLoad = nullptr);

	protected:
		LVL() = default;
		~LVL() = default;
	};
}