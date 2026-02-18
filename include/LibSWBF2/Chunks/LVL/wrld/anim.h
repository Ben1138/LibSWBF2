#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Chunks/LVL/wrld/anim.INFO.h>
#include <LibSWBF2/Chunks/LVL/wrld/WorldAnimKeyChunk.h>


namespace LibSWBF2::Chunks::LVL::wrld
{
	struct LIBSWBF2_API anim : public GenericChunk<"anim"_m>
	{
		anim_INFO* p_Info;

		List<POSK *> m_PositionKeys;
		List<ROTK *> m_RotationKeys;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}