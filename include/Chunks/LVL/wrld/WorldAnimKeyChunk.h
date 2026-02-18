#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/WorldAnimationKey.h"


namespace LibSWBF2::Chunks::LVL::wrld
{
	template<uint32_t Header>
	struct LIBSWBF2_API WorldAnimKeyChunk : public GenericChunk<Header>
	{
		Types::WorldAnimationKey m_Key;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};

	struct LIBSWBF2_API WorldAnimKeyChunkNC : public WorldAnimKeyChunk<0> {};
	struct LIBSWBF2_API POSK : public WorldAnimKeyChunk<"POSK"_m> {};
	struct LIBSWBF2_API ROTK : public WorldAnimKeyChunk<"ROTK"_m> {};
}
