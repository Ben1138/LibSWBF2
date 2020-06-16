#pragma once
#include "Chunks/BaseChunk.h"
#include "Chunks/STR.h"
#include "FRAM.h"
#include "BBOX.h"

namespace LibSWBF2::Chunks::MSH
{
	struct MSH2;

	struct LIBSWBF2_API SINF : public BaseChunk
	{
		SINF() = default;
		~SINF() = default;

		STR<"NAME"_m> m_Name;
		FRAM m_FrameInformation;
		BBOX m_BoundingBox;

	protected:
		friend MSH2;
		
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}