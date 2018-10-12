#pragma once
#include "BaseChunk.h"
#include "STRING.h"
#include "FRAM.h"
#include "BBOX.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MSH2;

	struct SINF : public BaseChunk
	{
		SINF() = default;
		~SINF() = default;

		STRING m_Name;
		FRAM m_FrameInformation;
		BBOX m_BoundingBox;

	protected:
		friend MSH2;
		
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}