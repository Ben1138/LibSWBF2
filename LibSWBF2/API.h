#pragma once
#include "Types/Enums.h"
#include "Logging/Logger.h"
#include "Wrappers/Level.h"


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
		struct Bone;
		class Terrain;
		class Light;

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
		LIBSWBF2_API void 	 STRP_CalcPolygons(Chunks::MSH::STRP* strp);
		LIBSWBF2_API EModelPurpose MODL_GetPurpose(Chunks::MSH::MODL* modl);

		// Wrappers - Level
		LIBSWBF2_API Level*  Level_FromFile(const char* path);
		LIBSWBF2_API void    Level_Destroy(Level* level);
		LIBSWBF2_API uint8_t Level_IsWorldLevel(const Level* level);
		LIBSWBF2_API void 	 Level_GetModels(const Level* level, const Model**& modelArr, uint32_t& modelCount);
		LIBSWBF2_API void 	 Level_GetWorlds(const Level* level, const World**& worldArr, uint32_t& worldCount);
		LIBSWBF2_API void 	 Level_GetTerrains(const Level* level, const Terrain**& terrainArr, uint32_t& terrainCount);
		LIBSWBF2_API void 	 Level_GetLights(const Level* level, const Light**& lightArr, uint32_t& lightCount);

		//LIBSWBF2_API void GetTextures(const Level* level, Texture**& modelArr, uint32_t& modelCount);
		//LIBSWBF2_API void GetTerrains(const Level* level, Terrain*& modelArr, uint32_t& modelCount);
		//LIBSWBF2_API void GetScripts(const Level* level, Script*& modelArr, uint32_t& modelCount);
					 
		LIBSWBF2_API const Model* Level_GetModel(const Level* level, const char* modelName);
		LIBSWBF2_API const bool   Level_GetTextureData(const Level* level, const char *texName, const uint8_t*& imgData, int& w, int&h);
		//LIBSWBF2_API const Texture* GetTexture(String textureName) const;
		//LIBSWBF2_API const World* GetWorld(String worldName) const;
		//LIBSWBF2_API const Terrain* GetTerrain(String terrainName) const;
		//LIBSWBF2_API const Script* GetScript(String scriptName) const;

		// Wrappers - Model
		LIBSWBF2_API const char* Model_GetName(const Model* model);
		LIBSWBF2_API const void  Model_GetSegments(const Model* model, const Segment**& segmentArr, uint32_t& segmentCount);
		LIBSWBF2_API uint8_t 	 Model_IsSkeletalMesh(const Model* model);
		LIBSWBF2_API uint8_t 	 Model_GetSkeleton(const Model* model, Bone*& boneArr, uint32_t& boneCount);

		// Wrappers - Segment
		LIBSWBF2_API const void    Segment_GetVertexBuffer(const Segment* segment, uint32_t& numVerts, float*& vertBuffer);
		LIBSWBF2_API const void    Segment_GetUVBuffer(const Segment* segment, uint32_t& numUVs, float*& UVBuffer);
		LIBSWBF2_API const void    Segment_GetIndexBuffer(const Segment* segment, uint32_t& numUVs, int*& indexBuffer);
		LIBSWBF2_API const void    Segment_GetNormalBuffer(const Segment* segment, uint32_t& numNormals, float*& normalsBuffer);
		LIBSWBF2_API const char*   Segment_GetMaterialTexName(const Segment* segment);
		LIBSWBF2_API const int32_t Segment_GetTopology(const Segment* segment);

		// Enums
		LIBSWBF2_API const char* ENUM_TopologyToString(ETopology topology);
		LIBSWBF2_API const char* ENUM_MaterialFlagsToString(EMaterialFlags flags);
		LIBSWBF2_API const char* ENUM_VBUFFlagsToString(EVBUFFlags flags);
		LIBSWBF2_API const char* ENUM_EVBUFFlagsToString(EVBUFFlags flags);

		// Wrappers - Terrain

		LIBSWBF2_API const void Terrain_GetTexNames(const Terrain *ter, uint32_t& numTexes, const char**& result);
		LIBSWBF2_API const void Terrain_GetHeightMap(const Terrain *ter, uint32_t& dim, uint32_t& dimScale, float_t*& heightData);
		LIBSWBF2_API const void Terrain_GetBlendMap(const Terrain *ter, uint32_t& width, uint32_t& numLayers, uint8_t*& data);
		LIBSWBF2_API const void Terrain_GetHeightBounds(const Terrain *ter, float_t& floor, float_t& ceiling);


		// Wrappers - World
        LIBSWBF2_API const char* World_GetName(const World* world);
        LIBSWBF2_API const void  World_GetInstances(const World* world, const Instance**& instanceArr, uint32_t& instCount);

        // Wrappers - Instance
        LIBSWBF2_API const char* 	Instance_GetName(const Instance* instance);
        LIBSWBF2_API const Vector4* Instance_GetRotation(const Instance* instance);
        LIBSWBF2_API const Vector3* Instance_GetPosition(const Instance* instance);

        // Wrappers - Vectors
		LIBSWBF2_API const void Vector4_FromPtr(const Vector4* vec, float_t& x, float_t& y, float_t& z, float_t &w);        
		LIBSWBF2_API const void Vector3_FromPtr(const Vector3* vec, float_t& x, float_t& y, float_t& z); 
		LIBSWBF2_API const void Vector2_FromPtr(const Vector2* vec, float_t& x, float_t& y); 
	
		// Wrappers - Light
		LIBSWBF2_API const char* Light_GetAllFields(const Light* lightPtr, Vector4*& rotPtr,
				                                    Vector3*& posPtr, uint32_t& lightType, 
				                                    Vector3*& colPtr, float_t& range,
				                                    Vector2*& conePtr);
	}
}
