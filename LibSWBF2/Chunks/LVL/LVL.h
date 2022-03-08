#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/Enums.h"

namespace LibSWBF2::Chunks::LVL
{
	namespace sound
	{
		struct Stream;
	}

	struct LIBSWBF2_API LVL : public GenericChunk<"ucfb"_m>
	{
	private:
		List<FNVHash> m_SubLVLsToLoad;
		bool m_Lazy;

	public:
		friend struct lvl_;

		static LVL* Create(bool Lazy = false);
		static void Destroy(LVL* lvl);

		void ReadFromStream(FileReader& stream) override;

		bool FindAndReadSoundStream(FileReader& stream, FNVHash soundStreamName, sound::Stream *& streamChunk);


		// All sub LVLs not specified in here won't be loaded!
		bool ReadFromFile(String Path, const List<String>* subLVLsToLoad = nullptr);


	protected:
		LVL() = default;
		~LVL() = default;
	};
}