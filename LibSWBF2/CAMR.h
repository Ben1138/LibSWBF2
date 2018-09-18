#pragma once
#include "BaseChunk.h"
#include "NAME.h"
#include "FRAM.h"
#include "BBOX.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MATL : public BaseChunk
	{
		MATL();
		~MATL();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		uint32_t m_Length;
	};
}