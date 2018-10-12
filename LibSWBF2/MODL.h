#pragma once
#include "BaseChunk.h"
#include "STRING.h"
#include "MTYP.h"
#include "MNDX.h"
#include "FLGS.h"
#include "TRAN.h"
#include "GEOM.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MSH2;

	struct MODL : public BaseChunk
	{
		MODL();
		~MODL();

		STRING m_Name;
		MTYP m_ModelType;
		MNDX m_ModelIndex;
		STRING m_Parent;
		FLGS m_Flags;
		TRAN m_Transition;
		GEOM m_Geometry;

	protected:
		friend MSH2;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}
