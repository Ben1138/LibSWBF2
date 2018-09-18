#pragma once
#include "BaseChunk.h"
#include "SHVO.h"
#include "MSH2.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MSH : public BaseChunk
	{
		MSH();
		~MSH();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		SHVO m_SHVO;
		MSH2 m_MSH2;
	};
}