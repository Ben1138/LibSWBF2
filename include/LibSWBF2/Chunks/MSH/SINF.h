#pragma once
#include <LibSWBF2/Chunks/BaseChunk.h>
#include <LibSWBF2/Chunks/STR.h>
#include <LibSWBF2/Chunks/MSH/FRAM.h>
#include <LibSWBF2/Chunks/MSH/BBOX.h>

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