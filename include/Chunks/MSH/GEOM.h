#pragma once
#include "Chunks/BaseChunk.h"
#include "BBOX.h"
#include "SEGM.h"
#include "ENVL.h"

namespace LibSWBF2::Chunks::MSH
{
	struct MODL;

	struct LIBSWBF2_API GEOM : public BaseChunk
	{
		GEOM() = default;
		~GEOM() = default;

		BBOX m_BoundingBox;
		List<SEGM> m_Segments;
		ENVL m_Envelope;

	protected:
		friend MODL;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}