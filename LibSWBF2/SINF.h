#pragma once
#include "BaseChunk.h"
#include "STRING.h"
#include "FRAM.h"
#include "BBOX.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct SINF : public BaseChunk
	{
		SINF();
		~SINF();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		STRING m_Name;
		FRAM m_FrameInformation;
		BBOX m_BoundingBox;
	};
}