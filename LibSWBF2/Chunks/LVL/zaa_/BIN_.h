#pragma once
#include "Chunks/GenericChunk.h"
//#include "SMNA.h"
#include "TADA.h"
#include "MINA.h"
#include "TNJA.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	struct LIBSWBF2_API BIN_ : public GenericChunk<"BIN_"_m>
	{
	public:
		//SMNA* p_SMNA;

		uint32_t m_Unknown1;
		uint32_t m_Unknown2;
		uint32_t m_Unknown3;

		uint16_t m_NumAnimations;
		uint16_t m_DebugLevel;

		MINA *p_AnimsMetadata;
		TNJA *p_JointAddresses;
		TADA *p_CompressedAnimData;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}