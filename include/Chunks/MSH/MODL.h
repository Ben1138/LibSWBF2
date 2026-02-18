#pragma once
#include <Chunks/BaseChunk.h>
#include <Chunks/STR.h>
#include <Types/Enums.h>
#include <Chunks/MSH/MTYP.h>
#include <Chunks/MSH/MNDX.h>
#include <Chunks/MSH/FLGS.h>
#include <Chunks/MSH/TRAN.h>
#include <Chunks/MSH/GEOM.h>
#include <Chunks/MSH/SWCI.h>

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
