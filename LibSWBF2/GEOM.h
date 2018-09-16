#pragma once
#include "BaseChunk.h"
#include "NAME.h"
#include "FRAM.h"
#include "BBOX.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct GEOM : public BaseChunk
	{
		GEOM();
		~GEOM();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

	private:
		BBOX bbox;
	};
}