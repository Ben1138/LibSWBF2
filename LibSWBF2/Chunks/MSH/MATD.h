#pragma once
#include "Chunks/BaseChunk.h"
#include "Chunks/STR.h"
#include "DATA.h"
#include "ATRB.h"

namespace LibSWBF2::Chunks::MSH
{
	struct MATL;

	struct LIBSWBF2_API MATD : public BaseChunk
	{
		MATD() = default;
		~MATD() = default;

		STR<"NAME"_m> m_Name;
		DATA m_Data;
		ATRB m_Attribute;
		STR<"TX0D"_m> m_Texture0;		// TX0D
		STR<"TX1D"_m> m_Texture1;		// TX1D
		STR<"TX2D"_m> m_Texture2;		// TX2D
		STR<"TX3D"_m> m_Texture3;		// TX3D

	protected:
		friend MATL;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}