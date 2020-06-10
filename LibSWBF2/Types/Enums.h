#pragma once
#include "req.h"
#include "LibString.h"

namespace LibSWBF2
{
	// Bitmap flags
	enum class EModelPurpose : uint16_t
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

	enum class EModelType : uint32_t
	{
		Null = 0,
		Skin = 1,
		Envelope = 3,
		Static = 4,
		Shadow = 6
	};

	enum class ELODLevel : uint8_t
	{
		NONE = 0,
		LOD1 = 1,
		LOD2 = 2,
		LOD3 = 3,
		LOWD = 4
	};

	enum class ETopology : int32_t 
	{
		PointList = 1,
		LineList = 2,
		LineStrip = 3,
		TriangleList = 4,
		TriangleStrip = 5,
		TriangleFan = 6
	};

	// copied from: https://github.com/SleepKiller/swbf-unmunge
	enum class EMaterialFlags : uint32_t
	{
		Normal = 1,
		Hardedged = 2,
		Transparent = 4,
		Glossmap = 8,
		Glow = 16,
		BumpMap = 32,
		Additive = 64,
		Specular = 128,
		EnvMap = 256,
		VertexLighting = 512,
		TiledNormalmap = 2048,
		Doublesided = 65536,

		Scrolling = 16777216,
		Energy = 33554432,
		Animated = 67108864,

		AttachedLight = 134217728,
	};

	enum class EVBUFFlags : uint32_t
	{
		None = 0b0u,
		Position = 0b10u,
		BlendIndices = 0b100u,
		BlendWeight = 0b1000u,
		Normal = 0b100000u,
		Tangents = 0b1000000u,
		Color = 0b10000000u,
		StaticLighting = 0b100000000u,
		TexCoord = 0b1000000000u,

		PositionCompressed = 0b1000000000000u,
		BlendWeightCompressed = 0b10000000000000u,
		NormalCompressed = 0b100000000000000u,
		TexCoordCompressed = 0b1000000000000000u
	};

	enum class ETextureFormat : uint8_t
	{
		R8_G8_B8_A8,
		B8_G8_R8_A8
	};

	String LIBSWBF2_EXP TopologyToString(ETopology topology);
	String LIBSWBF2_EXP MaterialFlagsToString(EMaterialFlags flags);
	String LIBSWBF2_EXP EVBUFFlagsToString(EVBUFFlags flags);

	EMaterialFlags operator &(EMaterialFlags lhs, EMaterialFlags rhs);
	bool operator ==(EMaterialFlags lhs, std::underlying_type<EMaterialFlags>::type rhs);
	bool operator !=(EMaterialFlags lhs, std::underlying_type<EMaterialFlags>::type rhs);
	EVBUFFlags operator &(EVBUFFlags lhs, EVBUFFlags rhs);
	bool operator ==(EVBUFFlags lhs, std::underlying_type<EVBUFFlags>::type rhs);
	bool operator !=(EVBUFFlags lhs, std::underlying_type<EVBUFFlags>::type rhs);
}
