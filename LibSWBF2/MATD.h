#pragma once
#include "BaseChunk.h"
#include "NAME.h"
#include "MATD_DATA.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MATD : public BaseChunk
	{
		MATD();
		~MATD();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		STRING m_NAME;
		MATD_DATA m_DATA;
		STRING m_TX0D;
		STRING m_TX1D;
		STRING m_TX2D;
		STRING m_TX3D;
	};
}