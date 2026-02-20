#pragma once
#include <LibSWBF2/Chunks/BaseChunk.h>
#include <LibSWBF2/Chunks/STR.h>
#include <LibSWBF2/Types/Enums.h>
#include <LibSWBF2/Chunks/MSH/MTYP.h>
#include <LibSWBF2/Chunks/MSH/MNDX.h>
#include <LibSWBF2/Chunks/MSH/FLGS.h>
#include <LibSWBF2/Chunks/MSH/TRAN.h>
#include <LibSWBF2/Chunks/MSH/GEOM.h>
#include <LibSWBF2/Chunks/MSH/SWCI.h>

namespace LibSWBF2::Chunks::MSH
{
	struct MSH2;

	struct LIBSWBF2_API MODL : public BaseChunk
	{
		MODL() = default;
		~MODL() = default;

		EModelPurpose GetPurpose();

		STR<"NAME"_m> m_Name;
		MTYP m_ModelType;
		MNDX m_ModelIndex;
		STR<"PRNT"_m> m_Parent;
		FLGS m_Flags;
		TRAN m_Transition;
		GEOM m_Geometry;
		SWCI m_CollisionPrimitive;

	protected:
		friend MSH2;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}
