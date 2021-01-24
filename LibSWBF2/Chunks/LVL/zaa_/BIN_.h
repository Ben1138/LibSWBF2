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


		//Always 8 for SWBF2 lvls, will abort read if a
		//diferent one is encountered.  Confirmed by 
		//ZAT files
		uint32_t m_Version; 

		uint32_t m_NumBones; 

		//Length of data buffer in TADA
		uint32_t m_DataBufferLength;

		uint16_t m_NumAnimations;

		//ZenAsset can pack a bunch of extra debug data
		//into TADA, essentially writing decompressed anims.
		//Will abort if not 0.
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