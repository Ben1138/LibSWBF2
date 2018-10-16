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

	enum EModelPurpose
	{
		RegularMesh = 0,
		LowrezMesh = 1,
		Collision = 2,
		VehicleCollision = 3,
		ShadowVolume = 4,
		TerrainCut = 5,
		HardPoint = 6,
		EmptyTransform = 7,
		BoneRoot = 8,
		BoneLimb = 9,
		BoneEnd = 10,
		Miscellaneous = 11,
	};

	struct MODL : public BaseChunk
	{
		MODL() = default;
		~MODL() = default;

		LIBSWBF2_EXP EModelPurpose GetEstimatedPurpose();

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
