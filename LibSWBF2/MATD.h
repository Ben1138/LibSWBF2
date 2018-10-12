#pragma once
#include "BaseChunk.h"
#include "STRING.h"
#include "MATD_DATA.h"
#include "ATRB.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MATL;

	struct MATD : public BaseChunk
	{
		MATD();
		~MATD();

		STRING m_Name;
		MATD_DATA m_Data;
		ATRB m_Attribute;
		STRING m_Texture0;		// TX0D
		STRING m_Texture1;		// TX1D
		STRING m_Texture2;		// TX2D
		STRING m_Texture3;		// TX3D

	protected:
		friend MATL;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}