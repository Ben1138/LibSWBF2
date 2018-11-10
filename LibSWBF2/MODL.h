#pragma once
#include "BaseChunk.h"
#include "STRING.h"
#include "MTYP.h"
#include "MNDX.h"
#include "FLGS.h"
#include "TRAN.h"
#include "GEOM.h"
#include "SWCI.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MSH2;

	// Bitmap flags
	enum EModelPurpose : uint16_t
	{
		// Unknown
		Miscellaneous = 0,

		// Meshes
		Mesh = 63,
		Mesh_Regular = 1,
		Mesh_Lowrez = 2,
		Mesh_Collision = 4,
		Mesh_VehicleCollision = 8,
		Mesh_ShadowVolume = 16,
		Mesh_TerrainCut = 32,

		// Just Points
		Point = 448,
		Point_EmptyTransform = 64,
		Point_DummyRoot = 128,
		Point_HardPoint = 256,

		// Skeleton
		Skeleton = 7680,
		Skeleton_Root = 512,
		Skeleton_BoneRoot = 1024,
		Skeleton_BoneLimb = 2048,
		Skeleton_BoneEnd = 4096,
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
		SWCI m_CollisionPrimitive;

	protected:
		friend MSH2;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}
