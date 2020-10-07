#pragma once
#include "Types/Enums.h"
#include "Logging/Logger.h"

namespace LibSWBF2
{
	class Container;

	namespace Chunks::MSH { struct MSH; }
	namespace Chunks::MSH { struct MODL; }
	namespace Chunks::MSH { struct STRP; }
	namespace Wrappers 
	{ 
		class Level; 
		class Model;
		class Segment;
		class Terrain;
		class CollisionMesh;
		struct Bone;
		class CollisionPrimitive;
		//class Texture;
		//class World;
		//class Script;
	}


	namespace Types
	{
		struct Vector4;
		struct Vector3;
	}

	using namespace Wrappers;
	using namespace Types;

	// Provide mangling free C-functions to be accessible from C# wrapper
	extern "C"
	{
		//Memory //
		LIBSWBF2_API void Memory_Blit(void *dest, void *src, int numBytes);


		// Logging //
		LIBSWBF2_API uint8_t LOG_GetNextLog(const char*& msg, ELogType& level, uint32_t& line, const char*& file);
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
		LIBSWBF2_API const bool Container_IsDone(Container* container);

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
					 
		LIBSWBF2_API const Model* Level_GetModel(const Level* level, const char* modelName);
		//LIBSWBF2_API const Texture* GetTexture(String textureName) const;
		//LIBSWBF2_API const World* GetWorld(String worldName) const;
		//LIBSWBF2_API const Script* GetScript(String scriptName) const;

		// Wrappers - Model
		LIBSWBF2_API const char* Model_GetName(const Model* model);
		LIBSWBF2_API const void Model_GetSegments(const Model* model, Segment*& segmentArr, uint32_t& segmentCount);
		LIBSWBF2_API uint8_t Model_IsSkeletalMesh(const Model* model);
		LIBSWBF2_API uint8_t Model_GetSkeleton(const Model* model, Bone*& boneArr, uint32_t& boneCount);
		LIBSWBF2_API const CollisionMesh* Model_GetCollisionMesh(const Model *model);
		LIBSWBF2_API const void Model_GetPrimitivesMasked(const Model* model, uint32_t mask, int& numPrims,
														CollisionPrimitive**& primArrayPtr);


		// Wrappers - Segment
		// ....

		// Wrappers - Terrain
		LIBSWBF2_API const void Terrain_GetTexNames(const Terrain *ter, uint32_t& numTexes, const char**& result);
		LIBSWBF2_API const void Terrain_GetHeightMap(const Terrain *ter, uint32_t& dim, uint32_t& dimScale, float_t*& heightData);
		LIBSWBF2_API const void Terrain_GetBlendMap(const Terrain *ter, uint32_t& width, uint32_t& numLayers, uint8_t*& data);
		LIBSWBF2_API const void Terrain_GetHeightBounds(const Terrain *ter, float& floor, float& ceiling);

		// Wrappers - CollisionMesh
		LIBSWBF2_API const void CollisionMesh_GetIndexBuffer(const CollisionMesh *collMesh, uint32_t& count, uint16_t*& buffer);
        LIBSWBF2_API const void CollisionMesh_GetVertexBuffer(const CollisionMesh *collMesh, uint32_t& count, float_t*& buffer);

        // Wrappers - CollisionPrimitive
        LIBSWBF2_API const void CollisionPrimitive_FetchAllFields(CollisionPrimitive *primPtr,
                                                    float_t& f1, float_t& f2, float_t& f3,
                                                    const char *& name, const char *& parentName,
                                                    uint32_t& maskFlags, uint32_t& primitiveType,
                                                    Vector3*& pos, Vector4*& rot);

		// Enums
		LIBSWBF2_API const char* ENUM_TopologyToString(ETopology topology);
		LIBSWBF2_API const char* ENUM_MaterialFlagsToString(EMaterialFlags flags);
		LIBSWBF2_API const char* ENUM_VBUFFlagsToString(EVBUFFlags flags);


		// Wrappers - Vectors
		LIBSWBF2_API const void Vector4_FromPtr(const Vector4* vec, float_t& x, float_t& y, float_t& z, float_t &w);        
		LIBSWBF2_API const void Vector3_FromPtr(const Vector3* vec, float_t& x, float_t& y, float_t& z); 
		LIBSWBF2_API const void Vector2_FromPtr(const Vector2* vec, float_t& x, float_t& y); 
	}
}