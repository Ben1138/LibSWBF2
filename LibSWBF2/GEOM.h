#pragma once
#include "BaseChunk.h"
#include "BBOX.h"
#include "SEGM.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MODL;

	struct GEOM : public BaseChunk
	{
		GEOM();
		~GEOM();

		BBOX m_BoundingBox;
		vector<SEGM> m_Segments;

	protected:
		friend MODL;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}