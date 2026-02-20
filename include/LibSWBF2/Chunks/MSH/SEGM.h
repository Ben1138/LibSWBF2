#pragma once
#include <LibSWBF2/Chunks/BaseChunk.h>
#include <LibSWBF2/Chunks/MSH/MATI.h>
#include <LibSWBF2/Chunks/MSH/POSL.h>
#include <LibSWBF2/Chunks/MSH/WGHT.h>
#include <LibSWBF2/Chunks/MSH/NRML.h>
#include <LibSWBF2/Chunks/MSH/UV0L.h>
#include <LibSWBF2/Chunks/MSH/STRP.h>

namespace LibSWBF2::Chunks::MSH
{
	struct GEOM;

	struct LIBSWBF2_API SEGM : public BaseChunk
	{
		SEGM() = default;
		~SEGM() = default;

		MATI m_MaterialIndex;
		POSL m_VertexList;
		WGHT m_WeightList;
		NRML m_NormalList;
		UV0L m_UVList;
		STRP m_TriangleList;

	protected:
		friend GEOM;
		
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}