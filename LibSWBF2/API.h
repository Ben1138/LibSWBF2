#pragma once
#include "Types/Enums.h"
#include "Logging/Logger.h"

namespace LibSWBF2
{
	class Container;

	namespace Chunks::MSH { struct MSH; }
	namespace Chunks::MSH { struct MODL; }
	namespace Chunks::MSH { struct STRP; }
	using Logging::LogCallback;
	namespace Wrappers 
	{ 
		class Level; 
		class Model;
		class Segment;
		class CollisionMesh;
		struct Bone;
		//class Texture;
		//class World;
		//class Terrain;
		//class Script;
	}
	using namespace Wrappers;

	// Provide mangling free C-functions to be accessible from C# wrapper
	extern "C"
	{
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

		// Wrappers - Container
        LIBSWBF2_API const Container* Container_Initialize();  
        LIBSWBF2_API uint32_t Container_AddLevel(Container* container, const char *path);
        LIBSWBF2_API float_t Container_GetProgress(Container* container, uint32_t handle);  
        LIBSWBF2_API const Level* Container_GetLevel(Container* container, uint32_t handle);
        LIBSWBF2_API const void* Container_GetWrapper(Container* container, uint32_t type, const char *name); 
        LIBSWBF2_API const void Container_LoadLevels(Container* container);

		// Wrappers - Level
		LIBSWBF2_API Level* Level_FromFile(const char* path);
		LIBSWBF2_API void Level_Destroy(Level* level);
		LIBSWBF2_API uint8_t Level_IsWorldLevel(const Level* level);
		LIBSWBF2_API void Level_GetModels(const Level* level, const Model**& modelArr, uint32_t& modelCount);
		//LIBSWBF2_API void GetTextures(const Level* level, Texture*& modelArr, uint32_t& modelCount);
		//LIBSWBF2_API void GetWorlds(const Level* level, World*& modelArr, uint32_t& modelCount);
		//LIBSWBF2_API void GetTerrains(const Level* level, Terrain*& modelArr, uint32_t& modelCount);
		//LIBSWBF2_API void GetScripts(const Level* level, Script*& modelArr, uint32_t& modelCount);
					 
		LIBSWBF2_API const Model* Level_GetModel(const Level* level, const char* modelName);
		//LIBSWBF2_API const Texture* GetTexture(String textureName) const;
		//LIBSWBF2_API const World* GetWorld(String worldName) const;
		//LIBSWBF2_API const Terrain* GetTerrain(String terrainName) const;
		//LIBSWBF2_API const Script* GetScript(String scriptName) const;

		// Wrappers - Model
		LIBSWBF2_API const char* Model_GetName(const Model* model);
		LIBSWBF2_API const void Model_GetSegments(const Model* model, Segment*& segmentArr, uint32_t& segmentCount);
		LIBSWBF2_API uint8_t Model_IsSkeletalMesh(const Model* model);
		LIBSWBF2_API uint8_t Model_GetSkeleton(const Model* model, Bone*& boneArr, uint32_t& boneCount);
		LIBSWBF2_API const CollisionMesh* Model_GetCollisionMesh(const Model *model);


		// Wrappers - Segment
		// ....

		// Wrappers - CollisionMesh
		LIBSWBF2_API const void CollisionMesh_GetIndexBuffer(const CollisionMesh *collMesh, uint32_t& count, int*& buffer);
        LIBSWBF2_API const void CollisionMesh_GetVertexBuffer(const CollisionMesh *collMesh, uint32_t& count, float_t*& buffer);



		// Enums
		LIBSWBF2_API const char* ENUM_TopologyToString(ETopology topology);
		LIBSWBF2_API const char* ENUM_MaterialFlagsToString(EMaterialFlags flags);
		LIBSWBF2_API const char* ENUM_VBUFFlagsToString(EVBUFFlags flags);
	}
}