#pragma once
#include "Types/Enums.h"
#include "Logging/Logger.h"

namespace LibSWBF2
{
	namespace Chunks::MSH { struct MSH; }
	namespace Chunks::MSH { struct MODL; }
	namespace Chunks::MSH { struct STRP; }
	using Logging::LogCallback;
	namespace Wrappers 
	{ 
		class Level; 
		class Model;
		class Segment;
		class Terrain;
		class CollisionMesh;
		struct Bone;
		//class Texture;
		//class World;
		//class Script;
	}
	using namespace Wrappers;

	// Provide mangling free C-functions to be accessible from C# wrapper
	extern "C"
	{

		//Explicit Mem Handling //
		LIBSWBF2_API void FreeFloatBuffer(float buffer[]);
		LIBSWBF2_API void FreeByteBuffer(uint8_t buffer[]);
		LIBSWBF2_API void FreeUIntBuffer(uint buffer[]);
		LIBSWBF2_API void FreeCharPtrBuffer(char * buffer[]);

		// Logging //
		LIBSWBF2_API void LOG_SetCallbackMethod(const LogCallback Callback);
		LIBSWBF2_API void LOG_SetLogfileLevel(ELogType LogfileLevel);

		// MSH //
		LIBSWBF2_API Chunks::MSH::MSH* MSH_Create();
		LIBSWBF2_API uint8_t MSH_Delete(Chunks::MSH::MSH* msh);
		LIBSWBF2_API uint8_t MSH_ReadFromFile(Chunks::MSH::MSH* msh, const char* path);
		LIBSWBF2_API uint8_t MSH_WriteToFile(Chunks::MSH::MSH* msh, const char* path);
		LIBSWBF2_API void STRP_CalcPolygons(Chunks::MSH::STRP* strp);
		LIBSWBF2_API EModelPurpose MODL_GetPurpose(Chunks::MSH::MODL* modl);

		// Wrappers - Level
		LIBSWBF2_API Level* Level_FromFile(const char* path);
		LIBSWBF2_API void Level_Destroy(Level* level);
		LIBSWBF2_API uint8_t Level_IsWorldLevel(const Level* level);
		LIBSWBF2_API void Level_GetModels(const Level* level, const Model**& modelArr, uint32_t& modelCount);
		LIBSWBF2_API void Level_GetTerrains(const Level* level, const Terrain**& terrainArr, uint32_t& terrainCount);
    	LIBSWBF2_API const bool Level_GetTextureData(const Level* level, const char *texName, const uint8_t*& imgData, int& width, int& height);

		//LIBSWBF2_API void GetTextures(const Level* level, Texture*& modelArr, uint32_t& modelCount);
		//LIBSWBF2_API void GetWorlds(const Level* level, World*& modelArr, uint32_t& modelCount);
		//LIBSWBF2_API void GetTerrains(const Level* level, Terrain*& modelArr, uint32_t& modelCount);
		//LIBSWBF2_API void GetScripts(const Level* level, Script*& modelArr, uint32_t& modelCount);
					 
		LIBSWBF2_API Model* Level_GetModel(Level* level, const char* modelName);
		//LIBSWBF2_API const Texture* GetTexture(String textureName) const;
		//LIBSWBF2_API const World* GetWorld(String worldName) const;
		//LIBSWBF2_API const Script* GetScript(String scriptName) const;

		// Wrappers - Model
		LIBSWBF2_API const char* Model_GetName(Model* model);
		LIBSWBF2_API const void Model_GetSegments(const Model* model, Segment*& segmentArr, uint32_t& segmentCount);
		LIBSWBF2_API uint8_t Model_IsSkeletalMesh(const Model* model);
		LIBSWBF2_API uint8_t Model_GetSkeleton(const Model* model, Bone*& boneArr, uint32_t& boneCount);
		LIBSWBF2_API const CollisionMesh* Model_GetCollisionMesh(const Model *model);

		// Wrappers - Segment
		// ....

		// Wrappers - Terrain
		LIBSWBF2_API const void Terrain_GetTexNames(const Terrain *ter, uint32_t& numTexes, const char**& result);
		LIBSWBF2_API const void Terrain_GetHeightMap(const Terrain *ter, uint32_t& dim, uint32_t& dimScale, float_t*& heightData);
		LIBSWBF2_API const void Terrain_GetBlendMap(const Terrain *ter, uint32_t& width, uint32_t& numLayers, uint8_t*& data);
		LIBSWBF2_API const void Terrain_GetHeightBounds(const Terrain *ter, float& floor, float& ceiling);

		// Wrappers - CollisionMesh
		LIBSWBF2_API const void CollisionMesh_GetIndexBuffer(CollisionMesh *collMesh, uint32_t& count, int*& buffer);
        LIBSWBF2_API const void CollisionMesh_GetVertexBuffer(const CollisionMesh *collMesh, uint32_t& count, float_t*& buffer);


		// Enums
		LIBSWBF2_API const char* ENUM_TopologyToString(ETopology topology);
		LIBSWBF2_API const char* ENUM_MaterialFlagsToString(EMaterialFlags flags);
		LIBSWBF2_API const char* ENUM_VBUFFlagsToString(EVBUFFlags flags);
	}
}