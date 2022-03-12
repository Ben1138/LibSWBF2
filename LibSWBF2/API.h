#pragma once
#include "Types/Enums.h"
#include "Logging/Logger.h"


namespace LibSWBF2
{
	class Container;
	class AudioStreamer;

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
		struct VertexWeight;
		class CollisionPrimitive;
		class AnimationBank;
		class AnimationSkeleton;
		struct Joint;
		class EntityClass;
		class Script;
		class WorldAnimationGroup;
		class WorldAnimationHierarchy;
		class WorldAnimation;
		class World;
		class Texture;
		class Config;
		class Material;
		class Instance;
		class Region;
		class Script;
		class Sound;
		class Localization;
		struct Field;
		struct Scope;
		class SoundStream;
		class SoundBank;
		//class FileReader;
	}

	namespace Types
	{
		struct Vector3;
		struct Vector4;
		struct Vector2;
		struct WorldAnimationKey;
	}

	using namespace Wrappers;
	using namespace Types;

	// Provide mangling free C-functions to be accessible from C# wrapper
	extern "C"
	{
		// Memory //
		LIBSWBF2_API void Memory_Blit(void *dest, void *src, int numBytes);

		// Hashing //
		LIBSWBF2_API uint8_t Hashing_Lookup(uint32_t hash, const char *& str);

		// FileReader //
		LIBSWBF2_API const FileReader * FileReader_FromFile(const char *path, bool UseMemoryMapping);
		LIBSWBF2_API const void FileReader_Delete(FileReader * readerPtr);


		// Logging //
		LIBSWBF2_API uint8_t LOG_GetNextLog(const char*& msg, ELogType& level, uint32_t& line, const char*& file);
		LIBSWBF2_API void LOG_SetLogfileLevel(ELogType LogfileLevel);

		// MSH //
		LIBSWBF2_API Chunks::MSH::MSH* MSH_Create();
		LIBSWBF2_API uint8_t MSH_Delete(Chunks::MSH::MSH* msh);
		LIBSWBF2_API uint8_t MSH_ReadFromFile(Chunks::MSH::MSH* msh, const char* path);
		LIBSWBF2_API uint8_t MSH_WriteToFile(Chunks::MSH::MSH* msh, const char* path);
		LIBSWBF2_API void 	 STRP_CalcPolygons(Chunks::MSH::STRP* strp);
		LIBSWBF2_API EModelPurpose MODL_GetPurpose(Chunks::MSH::MODL* modl);

		// Wrappers - Container
        LIBSWBF2_API const Container* Container_Initialize();  
        LIBSWBF2_API uint16_t Container_AddLevel(Container* container, const char *path);
		LIBSWBF2_API uint16_t Container_AddLevelFiltered(Container* container, const char* path, const char** subLVLs, uint32_t subLVLCount);
		LIBSWBF2_API void Container_FreeAll(Container* container, uint8_t force);
        LIBSWBF2_API float_t Container_GetProgress(Container* container, uint32_t handle);  
        LIBSWBF2_API float_t Container_GetOverallProgress(Container* container);  
        LIBSWBF2_API const Level* Container_GetLevel(Container* container, uint32_t handle);
		LIBSWBF2_API void Container_GetLoadedLevels(Container* container, uint16_t*& handles, uint16_t handleCount);
        LIBSWBF2_API uint8_t Container_GetStatus(Container* container, uint32_t handle);

		LIBSWBF2_API const void Container_LoadLevels(Container* container);
		LIBSWBF2_API const bool Container_IsDone(Container* container);
		LIBSWBF2_API const bool Container_Delete(Container* container);
		
		LIBSWBF2_API const void* Container_GetWrapper(Container* container, uint32_t type, const char *name); 
		LIBSWBF2_API const void* Container_GetWrapperFNV(Container* container, uint32_t type, uint32_t name); 
        LIBSWBF2_API const Config* Container_GetConfig(Container* container, uint32_t type, uint32_t nameHash); 


		// Wrappers - Level
		LIBSWBF2_API Level*  Level_FromFile(const char* path);
		LIBSWBF2_API Level*  Level_FromStream(FileReader* stream);
		LIBSWBF2_API void    Level_Destroy(Level* level);
		LIBSWBF2_API uint8_t Level_IsWorldLevel(const Level* level);

		LIBSWBF2_API const char *  Level_GetName(const Level* level);

		LIBSWBF2_API const Config*  Level_GetConfig(const Level* level, uint32_t header, uint32_t hash);
		LIBSWBF2_API const Config** Level_GetConfigs(const Level* level, uint32_t header, int32_t& numConfigs);

		LIBSWBF2_API const void* Level_GetWrapper(const Level* level, uint32_t type, const char* name);
		LIBSWBF2_API const void* Level_GetWrapperFNV(const Level* level, uint32_t type, uint32_t name);
		LIBSWBF2_API const void* Level_GetWrappers(const Level* level, uint32_t type, uint32_t& numWrappers, uint32_t& wrapperSize);

		LIBSWBF2_API SoundStream * Level_FindAndIndexSoundStream(Level * level, FileReader* stream, uint32_t StreamName);


		//Wrappers - Texture
		LIBSWBF2_API const uint8_t Texture_FetchAllFields(const Texture* tex, uint16_t& widthOut, uint16_t& heightOut, const uint8_t*& bufOut, const char*& nameOut);

		// Wrappers - Model
		LIBSWBF2_API const uint8_t Model_FetchSimpleFields(const Model* model,  const char*&name, uint8_t& skinned, uint8_t& skelBroken,
															const Segment*& segArr, int32_t& segCount, int32_t& segInc,
															const Bone*& boneArr, int32_t& boneCount, int32_t& boneInc,
														    const CollisionMesh*& collMeshPtr);

		LIBSWBF2_API const void  Model_GetPrimitivesMasked(const Model* model, uint32_t mask, int& numPrims,
														CollisionPrimitive**& primArrayPtr);

		// Wrappers - EntityClass
		LIBSWBF2_API void EntityClass_FetchAllFields(const EntityClass* ec, const char*& name, uint8_t& classType, const EntityClass*& baseClass, const char*& baseClassName);
		LIBSWBF2_API uint8_t EntityClass_GetPropertyFromName(const EntityClass *ec, const char* propName, const char*& value);
		LIBSWBF2_API uint8_t EntityClass_GetPropertyFromHash(const EntityClass *ec, uint32_t hashedPropName, const char*& value);
		LIBSWBF2_API uint8_t EntityClass_GetPropertiesFromName(const EntityClass *ec, const char* propName, const char**& values, uint32_t& count);
		LIBSWBF2_API uint8_t EntityClass_GetPropertiesFromHash(const EntityClass *ec, uint32_t hashedPropName, const char**& values, uint32_t& count);
		LIBSWBF2_API void EntityClass_GetOverriddenProperties(const EntityClass *ec, uint32_t*& hashesBuffer, const char**& valuesBuffer, int32_t &count);
		LIBSWBF2_API void EntityClass_GetAllProperties(const EntityClass* ec, uint32_t*& hashesBuffer, const char**& valuesBuffer, int32_t& count);

		// Wrappers - Bone
		LIBSWBF2_API const void Bone_FetchAllFields(const Bone* bone, const char *&name, const char *& parentName, const Vector3*& loc, const Vector4*& rot);

		// Wrappers - Segment		
		LIBSWBF2_API const uint8_t Segment_FetchAllFields(const Segment* seg, uint8_t& pretx, const char *&boneName, const char *&tag,
														uint32_t& numVerts, Vector3*& pBuf, Vector3*& nBuf, Vector2*&uvBuf,
														uint32_t& numVWs, VertexWeight*& vwBuf,
														int32_t& topo, uint32_t& numInds, uint16_t*& iBuf, 
														const Material*& mat);

        // Wrappers - CollisionPrimitive
        LIBSWBF2_API const void CollisionPrimitive_FetchAllFields(CollisionPrimitive *primPtr,
                                                    float_t& f1, float_t& f2, float_t& f3,
                                                    const char *& name, const char *& parentName,
                                                    uint32_t& maskFlags, uint32_t& primitiveType,
                                                    Vector3*& pos, Vector4*& rot);

		// Wrappers - CollisionMesh
        LIBSWBF2_API const uint8_t CollisionMesh_FetchAllFields(const CollisionMesh *cmPtr, uint32_t& iCount, uint16_t*& iBuf,
        														uint32_t& vCount, Vector3*& vBuf, uint32_t& maskFlags, 
        														const char *& namePtr, const char *& nodeNamePtr);

		// Enums
		LIBSWBF2_API const char* ENUM_TopologyToString(ETopology topology);
		LIBSWBF2_API const char* ENUM_MaterialFlagsToString(EMaterialFlags flags);
		LIBSWBF2_API const char* ENUM_EVBUFFlagsToString(EVBUFFlags flags);

		// Wrappers - Terrain
		LIBSWBF2_API const uint8_t Terrain_FetchSimpleFields(const Terrain* ter, int32_t &numTexes, const char**& texNames,
															float_t& heightUpper, float_t& heightLower, 
															uint32_t& numVerts, Vector3*& vBuf,
															uint32_t& numNormals, Vector3*& nBuf,
															uint32_t& numUVs, Vector2*& uvBuf);
		LIBSWBF2_API const void Terrain_GetHeightMap(const Terrain *ter, uint32_t& dim, uint32_t& dimScale, float_t*& heightData);
		LIBSWBF2_API const void Terrain_GetBlendMap(const Terrain *ter, uint32_t& width, uint32_t& numLayers, uint8_t*& data);
		LIBSWBF2_API const void Terrain_GetIndexBuffer(const Terrain *terr, uint32_t*& indicies, uint32_t& numInds);

		// Wrappers - Region
        LIBSWBF2_API const uint8_t Region_FetchAllFields(const Region* reg, const Vector3*& sizeOut, 
        											const Vector3*& posOut, const Vector4*& rotOut, 
        											const char *&nameOut, const char*& typeOut);
        // Wrappers - World
		LIBSWBF2_API const uint8_t World_FetchAllFields(const World* world, const char*&nameOut, const char*&skyNameOut,
										const Instance*& instanceArr, int32_t& instCount, int32_t& instInc,
										const Region*& regionArr, int32_t& regCount, int32_t& regInc,
										const WorldAnimation*& animArr, int32_t& animCount, int32_t& animInc,
										const WorldAnimationGroup*& animGroupArr, int32_t& animGroupCount, int32_t& animGroupInc,
										const WorldAnimationHierarchy*& animHierArr, int32_t& animHierCount, int32_t& animHierInc,
										const Terrain*& terrPtr);

		// Wrappers - WorldAnimation
		LIBSWBF2_API const uint8_t WorldAnim_FetchAllFields(const WorldAnimation* anim, uint8_t& loop, uint8_t& localT, const char*& namePtr);
        LIBSWBF2_API const void WorldAnim_GetAnimKeys(const WorldAnimation* anim, WorldAnimationKey*& keyBuff, int32_t& numKeys, uint8_t IsRotation);

		// Wrappers - WorldAnimationGroup
		LIBSWBF2_API const uint8_t WorldAnimGroup_FetchAllFields(const WorldAnimationGroup* group, uint8_t& bool0, uint8_t& bool1, const char*& namePtr);
        LIBSWBF2_API const void WorldAnimGroup_GetAnimInstPairs(const WorldAnimationGroup* group, const char**& animNames, const char**& instNames, int32_t& numKeys);

		// Wrappers - WorldAnimationHierarchy
    	LIBSWBF2_API const uint8_t WorldAnimHier_FetchAllFields(const WorldAnimationHierarchy* hier, const char *& rootPtr, const char**& childNames, int32_t& numChildren);


		// Wrappers - Script
		LIBSWBF2_API const char* Script_GetName(const Script* script);
		LIBSWBF2_API uint8_t Script_GetData(const Script* script, const uint8_t*& data, uint32_t& size);

        // Wrappers - Instance
   		LIBSWBF2_API const uint8_t Instance_FetchSimpleFields(const Instance* instPtr, const char*& name, Vector4*& rot, Vector3*& pos, const char*& ecName, const EntityClass*& ec);
		LIBSWBF2_API uint8_t Instance_GetPropertyFromName(const Instance* instPtr, const char* propName, const char*& value);
		LIBSWBF2_API uint8_t Instance_GetPropertyFromHash(const Instance* instPtr, uint32_t hashedPropName, const char*& value);
		LIBSWBF2_API uint8_t Instance_GetPropertiesFromName(const Instance* instPtr, const char* propName, const char**& values, uint32_t& count);
		LIBSWBF2_API uint8_t Instance_GetPropertiesFromHash(const Instance* instPtr, uint32_t hashedPropName, const char**& values, uint32_t& count);
   		LIBSWBF2_API void Instance_GetOverriddenProperties(const Instance *instPtr, uint32_t*& hashesBuffer, const char**& valuesBuffer, int32_t& count);

        // Wrappers - Material
        LIBSWBF2_API uint8_t Material_FetchAllFields(const Material* matPtr,  Vector3*& specular,
                                Vector3*& diffuse, char**& texPtrs, int32_t& numTexes,
                                char*& attachedLightName, uint32_t& matFlags, uint32_t& specExp,
                                uint32_t& param1, uint32_t& param2);

		// Wrappers - AnimationBank
		LIBSWBF2_API const bool AnimationBank_GetCurve(const AnimationBank* setPtr, uint32_t animCRC, uint32_t boneCRC, uint32_t comp, 
                                                        const uint16_t*& indicesBuffer, const float_t*& valuesBuffer, int32_t& numKeys);
        LIBSWBF2_API const uint32_t* AnimationBank_GetAnimationCRCs(const AnimationBank* setPtr, int32_t& numCRCs);
        LIBSWBF2_API const uint32_t* AnimationBank_GetBoneCRCs(const AnimationBank* setPtr, uint32_t animCRC, int32_t& numCRCs);
        LIBSWBF2_API const bool AnimationBank_GetAnimationMetadata(const AnimationBank* setPtr, uint32_t animCRC,
                                                        			int32_t& numFrames, int32_t& numBones);

        // Wrappers - AnimationSkeleton
        LIBSWBF2_API const char* AnimationSkeleton_GetName(const AnimationSkeleton* skelPtr);
        LIBSWBF2_API const uint8_t AnimationSkeleton_GetJoints(const AnimationSkeleton* skelPtr, int32_t& numJoints, Joint*& joints);


		// Wrappers - Sound
		LIBSWBF2_API uint8_t Sound_GetData(const Sound* sound, uint32_t& sampleRate, uint32_t& sampleCount, uint8_t& blockAlign, const uint8_t*& data);
		LIBSWBF2_API uint8_t Sound_FillDataBuffer(const Sound* sound, void* buffer);
        LIBSWBF2_API uint8_t Sound_FetchAllFields(const Sound* soundPtr, uint32_t& format, 
                                                int32_t& numChannels, int32_t& sampleRate,
                                                int32_t& numSamples, uint32_t& alias, 
                                                uint8_t& hasData, uint32_t& name, uint32_t& numBytes);



		// Wrappers - SoundStream
        LIBSWBF2_API const uint8_t SoundStream_FetchAllFields(
        		const SoundStream *str, uint32_t& nameOut, uint8_t& hasDataOut,
        		uint32_t& formatOut, uint32_t& numChannelsOut, uint32_t& numSubstreamsOut, uint32_t& substreamInterleaveOut);
        LIBSWBF2_API const uint8_t SoundStream_GetSound(const SoundStream *str, uint32_t soundName, const Sound*& soundOut);
        LIBSWBF2_API const uint8_t SoundStream_GetSounds(const SoundStream *str, const Sound*& soundsOut, uint32_t& numSounds, uint32_t& soundInc);

        LIBSWBF2_API const int32_t SoundStream_SampleReadMethod(
        		SoundStream *str, void * sBuf, int32_t sBufLength,
        		int32_t numToRead, ESoundFormat format, int32_t& numBytesRead, bool ReadSamples);
        
        LIBSWBF2_API const bool SoundStream_SetFileReader(SoundStream *str, FileReader * readerPtr);

        LIBSWBF2_API const bool SoundStream_SetStreamBuffer(SoundStream *str, void * bufferPtr, int32_t bufferLgenth);

        LIBSWBF2_API const int32_t SoundStream_ReadBytesFromStream(SoundStream *str, int32_t NumBytes);

        LIBSWBF2_API const int32_t SoundStream_GetNumSamplesInBytes(SoundStream *str, int32_t NumBytes);

    	LIBSWBF2_API const bool SoundStream_SetSegment(SoundStream *str, FNVHash name);
				
		// Wrappers - SoundBank
        LIBSWBF2_API const uint8_t SoundBank_FetchAllFields(
        		const SoundBank *str, uint32_t& nameOut, uint8_t& hasDataOut,
        		uint32_t& formatOut);
        LIBSWBF2_API const uint8_t SoundBank_GetSound(const SoundBank *str, uint32_t soundName, const Sound*& soundOut);
        LIBSWBF2_API const uint8_t SoundBank_GetSounds(const SoundBank *str, const Sound*& soundsOut, uint32_t& numSounds, uint32_t& soundInc);



		// Wrappers - Localization
		LIBSWBF2_API const char* Localization_GetName(const Localization* local);
		LIBSWBF2_API uint8_t Localization_GetLocalizedWideString(const Localization* local, const char* path, uint16_t*& chars, uint32_t& count);

        // Config
        LIBSWBF2_API const uint8_t Field_FetchAllFields(const Field *cfg, Scope*& scop);
        LIBSWBF2_API const Field** ConfigScope_GetFields(void *ptr, uint32_t hash, uint8_t isScope, uint32_t& count);

        LIBSWBF2_API const uint8_t Config_FetchSimpleFields(const Config* cfg, uint32_t& name);

		LIBSWBF2_API const uint32_t Field_GetNameHash(const Field* cfg);
		LIBSWBF2_API const uint8_t Field_GetNumValues(const Field* cfg);
        LIBSWBF2_API const float_t Field_GetFloat(const Field* cfg, uint8_t index);
        LIBSWBF2_API const uint32_t Field_GetUInt32(const Field* cfg, uint8_t index);
        LIBSWBF2_API const Vector2* Field_GetVec2(const Field* cfg); 
        LIBSWBF2_API const Vector3* Field_GetVec3(const Field* cfg); 
        LIBSWBF2_API const Vector4* Field_GetVec4(const Field* cfg); 
        LIBSWBF2_API const char* Field_GetString(const Field* cfg, uint8_t index);
		LIBSWBF2_API const char* Field_GetName(const Field* cfg);
	}
}
