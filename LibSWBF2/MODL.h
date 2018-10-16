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

	// Flags
	enum EModelPurpose : uint8_t
	{
		// Unknown
		Miscellaneous = 0,

		// Meshes
		RegularMesh = 1,
		LowrezMesh = 2,
		Collision = 3,
		VehicleCollision = 4,
		ShadowVolume = 5,
		TerrainCut = 6,

		// Just Points
		EmptyTransform = 7,
		HardPoint = 8,
		SkeletonRoot = 9,
		BoneRoot = 10,
		BoneLimb = 11,
		BoneEnd = 12,
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
