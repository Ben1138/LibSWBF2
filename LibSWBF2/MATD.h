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

	private:
		NAME m_NAME;
		MATD_DATA m_DATA;
		NAME m_TX0D;
		NAME m_TX1D;
		NAME m_TX2D;
		NAME m_TX3D;
	};
}