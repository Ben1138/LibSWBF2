#pragma once
#include "BaseChunk.h"
#include "STR.h"
#include "MATD_DATA.h"
#include "ATRB.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MATL;

	struct LIBSWBF2_EXP MATD : public BaseChunk
	{
		MATD() = default;
		~MATD() = default;

		STR m_Name;
		MATD_DATA m_Data;
		ATRB m_Attribute;
		STR m_Texture0;		// TX0D
		STR m_Texture1;		// TX1D
		STR m_Texture2;		// TX2D
		STR m_Texture3;		// TX3D

	protected:
		friend MATL;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}