#pragma once
#include "BaseChunk.h"
#include "STR.h"
#include "FRAM.h"
#include "BBOX.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MSH2;

	struct LIBSWBF2_EXP SINF : public BaseChunk
	{
		SINF() = default;
		~SINF() = default;

		STR m_Name;
		FRAM m_FrameInformation;
		BBOX m_BoundingBox;

	protected:
		friend MSH2;
		
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}