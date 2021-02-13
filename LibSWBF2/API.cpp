#include "stdafx.h"
#include "API.h"
#include "InternalHelpers.h"
#include "Types/LibString.h"
#include "Chunks/MSH/MSH.h"

#include <string.h>
#include "Wrappers/Level.h"
#include "Container.h"
#include "Wrappers/Terrain.h"
#include "Wrappers/Segment.h"
#include "Wrappers/Config.h"

#include "Chunks/HeaderNames.h"


namespace LibSWBF2
{

#define PurgePtr(ptr) delete[] ptr; ptr = nullptr;

#define CheckPtr(obj, ret) if (obj == nullptr) { LOG_ERROR("[API] Given Pointer was NULL!"); return ret; }

	// Helpers
	char ** GetStringListPtrs(const List<String>& strings)
	{
		char** ptrs = new char*[strings.Size()];
		for (int i = 0; i < strings.Size(); i++)
		{
			ptrs[i] = const_cast<char *>(strings[i].Buffer());
		}
		return ptrs;
	}


	// Memory //
	void Memory_Blit(void *dest, void *src, int numBytes)
	{
		memcpy(dest, src, numBytes);
	}

	// Logging //
	uint8_t LOG_GetNextLog(const char*& msg, ELogType& level, uint32_t& line, const char*& file)
	{
		static Logging::LoggerEntry current;
		bool hasLogEntry = Logging::Logger::GetNextLog(current);
		msg = current.m_Message.Buffer();
		level = current.m_Level;
		line = current.m_Line;
		file = current.m_File.Buffer();
		return hasLogEntry;
	}

	void LOG_SetLogfileLevel(ELogType LogfileLevel)
	{
		Logging::Logger::SetLogfileLevel(LogfileLevel);
	}


	// MSH //
	Chunks::MSH::MSH* MSH_Create()
	{
		return Chunks::MSH::MSH::Create();
	}

	uint8_t MSH_Delete(Chunks::MSH::MSH* msh)
	{
		CheckPtr(msh, false)
		LibSWBF2::Chunks::MSH::MSH::Destroy(msh);
		return true;
	}

	uint8_t MSH_ReadFromFile(Chunks::MSH::MSH* msh, const char* path)
	{
		CheckPtr(msh, false)
		return msh->ReadFromFile(path);
	}

	uint8_t MSH_WriteToFile(Chunks::MSH::MSH* msh, const char* path)
	{
		CheckPtr(msh, false)
		return msh->WriteToFile(path);
	}

	void STRP_CalcPolygons(Chunks::MSH::STRP* strp)
	{
		CheckPtr(strp,)
		strp->CalcPolygons();
	}

	EModelPurpose MODL_GetPurpose(Chunks::MSH::MODL* modl)
	{
		CheckPtr(modl, EModelPurpose::Miscellaneous)
		return modl->GetPurpose();
	}

	const Container* Container_Initialize()
	{
		return Container::Create();
	}

	uint32_t Container_AddLevel(Container* container, const char *path)
	{
		return (uint32_t) container -> AddLevel(path);
	}

	float_t Container_GetProgress(Container* container, uint32_t handleNum)
	{
		CheckPtr(container, -1.0f)
		return container -> GetLevelProgress((uint16_t) handleNum);
	}  

	const bool Container_IsDone(Container* container)
	{
		CheckPtr(container, false);
		return container -> IsDone();
	}

	const Level* Container_GetLevel(Container* container, uint32_t handleNum)
	{
		CheckPtr(container,nullptr);
		return container -> GetLevel((uint16_t) handleNum);
	}

	const void Container_LoadLevels(Container* container)
	{
		CheckPtr(container,);
		container -> StartLoading();
	}

	/*
	wrapperMap[typeof(Light)]         = 0;
    wrapperMap[typeof(Model)]         = 1;
    wrapperMap[typeof(Texture)]       = 2;
    wrapperMap[typeof(World)]         = 3;
    wrapperMap[typeof(EntityClass)]   = 4;
    wrapperMap[typeof(AnimationBank)] = 5;
	*/

	const void* Container_GetWrapper(Container* container, uint32_t type, const char *name)
	{
		switch (type)
		{
			case 0:
				//return static_cast<const void *>(container -> FindLight(name));
			case 1:
				return static_cast<const void *>(container -> FindModel(name));
			case 2:
				return static_cast<const void *>(container -> FindTexture(name));
			case 3:
				return static_cast<const void *>(container -> FindWorld(name));
			case 4:
				return static_cast<const void *>(container -> FindEntityClass(name));
			case 5:
				return static_cast<const void *>(container -> FindAnimationBank(name));
			default:
				return nullptr;
		}
	}


	const Config* Container_GetConfig(Container* container, uint32_t type, uint32_t nameHash)
	{
		CheckPtr(container,nullptr);
		return container -> FindConfig((EConfigType) type, nameHash);
	}



	const bool Container_Delete(Container* container)
	{
		CheckPtr(container,false);
		Container::Delete(container);
		return true;
	}



	// Wrappers
	Level* Level_FromFile(const char* path)
	{
		CheckPtr(path, nullptr);
		return Level::FromFile(path);
	}

	void Level_Destroy(Level* level)
	{
		CheckPtr(level,);
		Level::Destroy(level);
	}

	uint8_t Level_IsWorldLevel(const Level* level)
	{
		CheckPtr(level, false);
		return level->IsWorldLevel();
	}

	const EntityClass* Level_GetEntityClass(const Level* level, const char* name)
	{
		CheckPtr(level, nullptr);
		return level->GetEntityClass(name);		
	}


	const Model* Level_GetModel(const Level* level, const char* modelName)
	{
		CheckPtr(level, nullptr);
		return level->GetModel(modelName);
	}


	void Level_GetModels(const Level* level, const void*& modelArr, uint32_t& modelCount, int32_t& inc)
	{
		const List<Model>& models = level->GetModels();
		modelArr = (void *) models.GetArrayPtr();
		modelCount = (uint32_t) models.Size();
		inc = sizeof(Model);
	}


	void Level_GetEntityClasses(const Level* level, const void*& classArr, int32_t& classCount, int32_t& inc)
	{
		const List<EntityClass>& classes = level->GetEntityClasses();
		classArr = (void *) classes.GetArrayPtr();
		classCount = (int32_t) classes.Size();
		inc = sizeof(EntityClass);
	}


	const Texture* Level_GetTexture(const Level* level, const char* texName)
	{
		CheckPtr(level, nullptr);
		return level->GetTexture(texName);
	}



	void Level_GetTerrains(const Level* level, const Terrain**& terrainArr, uint32_t& terrainCount)
	{
		CheckPtr(level, );
		const List<Terrain>& terrains = level->GetTerrains();

		static List<const Terrain*> terrainPtrs;
		terrainPtrs.Clear();

		for (size_t i = 0; i < terrains.Size(); ++i)
		{
			terrainPtrs.Add(&terrains[i]);
		}

		terrainArr = terrainPtrs.GetArrayPtr();
		terrainCount = (uint32_t)terrainPtrs.Size();
	}


	void Level_GetWorlds(const Level* level, const World**& worldArr, uint32_t& worldCount)
	{
		CheckPtr(level, );
		const List<World>& worlds = level->GetWorlds();

		// since level->GetModels() just returns a reference to the actual list
		// member of level, which will persist even after this call ended, we can safely
		// provide the model addresses of the underlying buffer to the inquirer.
		// The inquirer of course is not allowed to alter the data!
		static List<const World*> worldPtrs;
		worldPtrs.Clear();

		for (size_t i = 0; i < worlds.Size(); ++i)
		{
			worldPtrs.Add(&worlds[i]);
		}

		worldArr = worldPtrs.GetArrayPtr();
		worldCount = (uint32_t) worldPtrs.Size();
	}


	const AnimationBank* Level_GetAnimationBank(const Level* level, const char* setName)
	{
		CheckPtr(level, nullptr);
		return level -> GetAnimationBank(setName);
	}


	char* Level_GetName(const Level* level)
	{
		static String cache;
		CheckPtr(level, nullptr);
		cache = level -> GetLevelName();
		return const_cast<char *>(cache.Buffer());
	}




	//Wrappers - Texture

	const uint8_t Texture_FetchAllFields(const Texture* tex, int32_t& widthOut, int32_t& heightOut, const uint8_t*& bufOut, const char*& nameOut)
	{
		static String nameCache;
		static const uint8_t* imageDataCache = nullptr;
    	//PurgePtr(imageDataCache);

		CheckPtr(tex,false);

		nameCache = tex -> GetName();
		nameOut = nameCache.Buffer();

		uint16_t w,h;
	    bool conversionStatus = tex -> GetImageData(ETextureFormat::R8_G8_B8_A8, 0, w, h, imageDataCache);

	    widthOut = w;
	    heightOut = h;
    	
    	if (conversionStatus)
    	{
    		bufOut = imageDataCache;
    	}
    	else
    	{
    		imageDataCache = nullptr;
    	}

    	return conversionStatus;
	}


	const Config* Level_GetConfig(const Level* level, uint32_t header, uint32_t hash)
	{
		const Config *ptr = nullptr;
		EConfigType cfgType = static_cast<EConfigType>(header);

		ptr = level -> GetConfig(cfgType, hash);

		return ptr;
	}

	const Config** Level_GetConfigs(const Level* level, uint32_t header, int32_t& numConfigs)
	{
		static List<const Config *> configs;
		EConfigType cfgType = static_cast<EConfigType>(header);

		configs = level -> GetConfigs(cfgType);
		
		numConfigs = configs.Size();
		return configs.GetArrayPtr();
	}

	const char* ENUM_TopologyToString(ETopology topology)
	{
		static Types::String lastToString;
		lastToString = TopologyToString(topology);
		return lastToString.Buffer();
	}


	
	//Wrappers - Terrain
	const uint8_t Terrain_FetchSimpleFields(const Terrain* ter, int32_t &numTexes, char**& texNamesOut,
											float_t& hU, float_t& hL, uint32_t& numVerts, Vector3*& vBuf,
											uint32_t& numNormals, Vector3*& nBuf, uint32_t& numUVs, Vector2*& uvBuf)
	{
		static char** texNamesPtrs = nullptr;
		PurgePtr(texNamesPtrs);
		CheckPtr(ter,false);

		const List<String>& texNames = ter -> GetLayerTextures();
        numTexes = texNames.Size();
        texNamesPtrs = GetStringListPtrs(texNames);
        texNamesOut = texNamesPtrs;

		ter -> GetHeightBounds(hL, hU);
		ter -> GetVertexBuffer(numVerts, vBuf);
		ter -> GetNormalBuffer(numNormals, nBuf);
		ter -> GetUVBuffer(numUVs, uvBuf);

		return true;
	}

    const void Terrain_GetHeightMap(const Terrain *ter, uint32_t& dim, uint32_t& dimScale, float_t*& heightData)
    {
    	dim = 0;
    	CheckPtr(ter, );
    	ter -> GetHeightMap(dim, dimScale, heightData);
    }

	const void Terrain_GetBlendMap(const Terrain *ter, uint32_t& dim, uint32_t& numLayers, uint8_t*& data)
	{	
		dim = 0;
    	CheckPtr(ter, );
		ter -> GetBlendMap(dim, numLayers, data);
	}

	const void Terrain_GetIndexBuffer(const Terrain *terr, uint32_t*& indicies, uint32_t& numInds)
	{
		if (terr == nullptr || !terr -> GetIndexBuffer(ETopology::TriangleList, numInds, indicies))
		{
			numInds = 0;
		}
	}




	// Wrappers - Model 
	const uint8_t Model_FetchSimpleFields(const Model* model, const char*& name, uint8_t& skinned, uint8_t& skelBroken,
										const Segment*& segArr, int32_t& segCount, int32_t& segInc,
										const Bone*& boneArr, int32_t& boneCount, int32_t& boneInc,
									    const CollisionMesh*& collMeshPtr)
	{
		static List<Bone> boneCache;

		CheckPtr(model,false);

		name = model -> GetName().Buffer();

		skinned = model -> IsSkeletalMesh();
		skelBroken = model -> IsSkeletonBroken();
		
		const List<Segment>& segs = model -> GetSegments();
		segArr = segs.GetArrayPtr();
		segCount = segs.Size();
		segInc = sizeof(Segment);

		boneCount = 0;
		if (model -> GetSkeleton(boneCache)){ boneCount = boneCache.Size(); }
		boneArr = boneCache.GetArrayPtr();
		boneInc = sizeof(Bone);

		collMeshPtr = &(model -> GetCollisionMesh());

		return true; 
	}

	const void Model_GetPrimitivesMasked(const Model* model, uint32_t mask, int& numPrims,
										CollisionPrimitive**& primArrayPtr)
	{
		static List<CollisionPrimitive> primsList;
		static List<CollisionPrimitive *> primPtrs;
		
		numPrims = 0;
		CheckPtr(model,);

		primsList = model -> GetCollisionPrimitives((ECollisionMaskFlags) mask);
		primPtrs.Clear();

		for (size_t i = 0; i < primsList.Size(); i++)
		{
			primPtrs.Add(&primsList[i]);
		}		

		primArrayPtr = primPtrs.GetArrayPtr();
		numPrims = (uint32_t) primPtrs.Size();		
	}


	// Wrappers - Bone
	const void Bone_FetchAllFields(const Bone* bone, const char *&name,
									const char *& parentName, const Vector3*& loc,
									const Vector4*& rot)
	{
	    name = (bone -> m_BoneName).Buffer();
	    loc = &(bone -> m_Position);
		rot = &(bone -> m_Rotation);
		parentName = (bone -> m_Parent).Buffer();
	}


	// Wrappers - CollisionMesh
    const uint8_t CollisionMesh_FetchAllFields(const CollisionMesh *cmPtr, uint32_t& iCount, uint16_t*& iBuf,
        										uint32_t& vCount, Vector3*& vBuf, uint32_t& maskFlags)
    {
    	CheckPtr(cmPtr, false);
    	cmPtr -> GetIndexBuffer(ETopology::TriangleList, iCount, iBuf);
    	cmPtr -> GetVertexBuffer(vCount, vBuf);
    	maskFlags = (uint32_t) cmPtr -> GetMaskFlags();
    	return true;
    }


    //Wrappers - CollisionPrimitive
    const void CollisionPrimitive_FetchAllFields(CollisionPrimitive *primPtr,
                                            float_t& f1, float_t& f2, float_t& f3,
                                            const char *& namePtr, const char *& parentNamePtr,
                                            uint32_t& maskFlags, uint32_t& primitiveType,
                                            Vector3*& pos, Vector4*& rot)
    {
    	static String name, parentName;
    	static Vector3 posTemp;
    	static Vector4 rotTemp;

    	f1 = f2 = f3 = 0.0f;

    	name = primPtr -> GetName();
    	parentName = primPtr -> GetParentName();

    	namePtr = name.Buffer();
    	parentNamePtr = parentName.Buffer();

    	maskFlags = (uint32_t) primPtr -> GetMaskFlags();
    	primitiveType = (uint32_t) primPtr -> GetPrimitiveType();

    	rotTemp = primPtr -> GetRotation();
    	posTemp = primPtr -> GetPosition();

    	pos = &posTemp; 
    	rot = &rotTemp; 

    	switch (primitiveType)
    	{
    		case 1:
    			primPtr -> GetSphereRadius(f1);
    			return;
    		case 2:
    			primPtr -> GetCylinderDims(f1,f2);
    			return;
    		case 4:
    			primPtr -> GetCubeDims(f1,f2,f3);
    			return;
    		default:
    			return;
    	}
    }

    

    //Wrappers - Segment
    const uint8_t Segment_FetchAllFields(const Segment* seg, uint8_t& pretx, const char *&boneName,
														uint32_t& numVerts, Vector3*& pBuf, Vector3*& nBuf, Vector2*&uvBuf,
														uint32_t& numVWs, VertexWeight*& vwBuf,
														int32_t& topo, uint32_t& numInds, uint16_t*& iBuf,
														const Material*& mat)
    {
    	static String boneNameCache;
    	CheckPtr(seg, false);

    	pretx = seg -> IsPretransformed();
    	
    	boneNameCache = seg -> GetBone();
    	boneName = boneNameCache.Buffer();

    	//Handle vertex buffers
    	uint32_t numNormals, numUVs;
    	seg -> GetVertexBuffer(numVerts, pBuf);
    	seg -> GetNormalBuffer(numNormals, nBuf);
    	seg -> GetUVBuffer(numUVs, uvBuf);

    	if (numUVs != numNormals || numNormals != numVerts)
    	{
    		LOG_ERROR("Buffer length mismatch!");
    		return false;
    	}

    	//Handle index buffer
    	topo = (int32_t) seg -> GetTopology();
    	seg -> GetIndexBuffer(numInds, iBuf);

    	//Handle weights
    	numVWs = seg -> GetVertexWeights(numVWs, vwBuf) ? numVWs : 0;

    	//Material
    	mat = &(seg -> GetMaterial());
    	return true;
    }



    // Wrappers - Material
    uint8_t Material_FetchAllFields(const Material* matPtr,  Vector3*& specular,
                    Vector3*& diffuse, char**& texPtrs, int32_t& numTexes,
                    char*& attachedLightName, uint32_t& matFlags, uint32_t& specExp)
    {	
    	static Vector3 specCache, diffCache;
    	static char** texNamePtrsCache = new char*[4];
    	static String namesCache[4];
    	static char* attachedLightNameCache = nullptr;

    	CheckPtr(matPtr, false);

    	numTexes = 0;
    	while (numTexes < 4 && matPtr -> GetTextureName(numTexes, namesCache[numTexes]))
    	{
    		texNamePtrsCache[numTexes] = const_cast<char *>(namesCache[numTexes].Buffer());
    		numTexes++;
    	}

    	texPtrs = texNamePtrsCache;

    	specExp = matPtr -> GetSpecularExponent();
    	matFlags = (uint32_t) matPtr -> GetFlags();  

    	Color4u8 d = matPtr -> GetDiffuseColor();
    	Color4u8 s = matPtr -> GetSpecularColor();

    	diffCache = Vector3(d.m_Red,d.m_Green,d.m_Blue); 
    	specCache = Vector3(s.m_Red,s.m_Green,s.m_Blue);

    	diffuse = &diffCache;
    	specular = &specCache; 

    	attachedLightName = const_cast<char *>(matPtr -> GetAttachedLight().Buffer());

    	return true;
    }


	const char* ENUM_MaterialFlagsToString(EMaterialFlags flags)
	{
		static Types::String lastToString;
		lastToString = MaterialFlagsToString(flags);
		return lastToString.Buffer();
	}

	const char* ENUM_VBUFFlagsToString(EVBUFFlags flags)
	{
		static String lastToString;
		lastToString = VBUFFlagsToString(flags);
		return lastToString.Buffer();
	}


	//Wrappers - World
	const void World_GetRegions(const World* world, const void*& regArr, uint32_t& count)
	{
		List<regn *>& regionChunks = world -> p_World -> m_Regions;
		regArr = (void *) regionChunks.GetArrayPtr();
		count = regionChunks.Size();
	}

	const void Region_FetchAllFields(const void* reg, Vector3*& sizeOut, Vector3*& posOut, Vector4*& rotOut, char *&nameOut, char*& typeOut)
	{
		static Vector4 rotCache;
		regn *regPtr = (regn *) reg;

		sizeOut = &(regPtr -> p_Info -> p_SIZE -> m_Dimensions);

		posOut = &(regPtr -> p_Info -> p_XFRM -> m_Position);
		
		rotCache = MatrixToQuaternion(regPtr -> p_Info -> p_XFRM -> m_RotationMatrix);
		rotOut = &rotCache;

		nameOut = const_cast<char *>(regPtr -> p_Info -> p_Name -> m_Text.Buffer());
		typeOut = const_cast<char *>(regPtr -> p_Info -> p_Type -> m_Text.Buffer());
	}

	const uint8_t World_FetchAllFields(const World* world, const char*&nameOut, const char*&skyNameOut,
										const Instance*& instanceArr, int32_t& instCount, int32_t& instInc,
										const Terrain*& terrPtr)
	{
		CheckPtr(world,false);
		static String skyNameCache;

		nameOut = world -> GetName().Buffer();

		skyNameCache = world -> GetSkyName();
		skyNameOut = skyNameCache.Buffer();

    	const List<Instance>& instances = world -> GetInstances();
		instanceArr = instances.GetArrayPtr();
		instCount = instances.Size();
		instInc = sizeof(Instance);

		terrPtr = world -> GetTerrain();

		return true;
	}

    

    // Wrappers - Instance
    const uint8_t Instance_FetchSimpleFields(const Instance* instPtr, const char*& name, Vector4*& rot, Vector3*& pos, const char*& ecName)
    {
    	static Vector4 rotCache;
    	static Vector3 posCache;
    	CheckPtr(instPtr,false);

    	name = instPtr -> GetName().Buffer();
    	ecName = instPtr -> GetType().Buffer();

    	rotCache = instPtr -> GetRotation();
    	posCache = instPtr -> GetPosition();

    	rot = &rotCache;
    	pos = &posCache;

    	return true;
    }

    const uint8_t Instance_GetOverriddenProperties(const Instance *instPtr, uint32_t*& hashesBuffer, char **& valuesBuffer, int32_t& count)
    {
    	CheckPtr(instPtr, false)
    	static List<String> values;
    	static List<uint32_t> hashes;
    	static char** ptrsBuffer = nullptr;

    	PurgePtr(ptrsBuffer);

    	if (instPtr -> GetOverriddenProperties(hashes, values))
    	{
    		hashesBuffer = hashes.GetArrayPtr();
    		count = values.Size();
			ptrsBuffer = GetStringListPtrs(values);
    		valuesBuffer = ptrsBuffer;
    		return true;
    	}

    	return false;
    }


    //Wrappers - EntityClass
    const char * EntityClass_GetProperty(const EntityClass *ec, const char *propName)
    {
    	CheckPtr(ec,"")
    	static String value; 

		if (ec -> GetProperty(propName, value))
		{
			return value.Buffer();
		}

		return "";
    }


    const char *EntityClass_GetName(const EntityClass *ec)
    {
    	CheckPtr(ec,"")
    	static String typeName;

    	typeName = ec -> GetTypeName();
    	return typeName.Buffer();     	
    }


    const char *EntityClass_GetBaseName(const EntityClass *ec)
    {
    	CheckPtr(ec,"")
    	static String baseName;

    	baseName = ec -> GetBaseName();
    	return baseName.Buffer(); 
    }


    uint8_t EntityClass_GetOverriddenProperties(const EntityClass *ec, uint32_t*& hashesBuffer, char **& valuesBuffer, int32_t& count)
    {
    	CheckPtr(ec, false)
    	char **ptrsBuffer = nullptr;
    	static List<String> values;
    	static List<uint32_t> hashes;

    	PurgePtr(ptrsBuffer);

    	if (!ec -> GetOverriddenProperties(hashes, values)){ return false; }
    	
		hashesBuffer = hashes.GetArrayPtr();
		count = values.Size();
		ptrsBuffer = GetStringListPtrs(values);
		valuesBuffer = ptrsBuffer;
		return true;
    }
   


    // Wrappers - AnimationBank
	const bool AnimationBank_GetCurve(const AnimationBank* setPtr, uint32_t animCRC, uint32_t boneCRC, uint32_t comp, 
                                                    const uint16_t*& indicesBuffer, const float_t*& valuesBuffer, int& numKeys)
	{
		static List<uint16_t> indices;
		static List<float_t>  values;

		CheckPtr(setPtr, false);

		bool status = setPtr -> GetCurve(animCRC, boneCRC, comp, indices, values);

		if (status)
		{
			numKeys = values.Size();
			indicesBuffer = indices.GetArrayPtr();
			valuesBuffer  = values.GetArrayPtr();
		}

		return status;
	}


    const uint32_t* AnimationBank_GetAnimationCRCs(const AnimationBank* setPtr, int& numCRCs)
    {
    	static List<uint32_t> crcs;

    	numCRCs = 0;
    	CheckPtr(setPtr, nullptr);

    	crcs = setPtr -> GetAnimationNames();
    	
    	numCRCs = crcs.Size();
    	return crcs.GetArrayPtr();
    }
    

    const bool AnimationBank_GetAnimationMetadata(const AnimationBank* setPtr, uint32_t animCRC,
                                                    int32_t& numFrames, int32_t& numBones)
    {
		CheckPtr(setPtr, false);
		uint32_t frames, bones;
		bool status = setPtr -> GetAnimationMetadata(animCRC, frames, bones);
		
		numFrames = frames;
		numBones = bones;
		return status;
    }


    const uint32_t Config_GetName(const Config* cfg)
    {
    	return cfg -> m_Name;
    }

    const uint8_t Config_IsPropertySet(const Config* cfg, uint32_t hash)
    {
    	return cfg -> IsPropertySet(hash);
    }

	const float_t Config_GetFloat(const Config* cfg, uint32_t hash)
	{
		return cfg -> GetFloat(hash);
	}

	const Vector2* Config_GetVec2(const Config* cfg, uint32_t hash)
	{
		static Vector2 cache;
		cache = cfg -> GetVector2(hash);
		return &cache; 
	}

	const Vector3* Config_GetVec3(const Config* cfg, uint32_t hash)
	{
		static Vector3 cache;
		cache = cfg -> GetVector3(hash);
		return &cache; 
	}

	const Vector4* Config_GetVec4(const Config* cfg, uint32_t hash)
	{
		static Vector4 cache;
		cache = cfg -> GetVector4(hash);
		return &cache; 
	}

	const char* Config_GetString(const Config* cfg, uint32_t hash)
	{
		static String cache;
		cache = cfg -> GetString(hash);
		return cache.Buffer(); 
	}

	const char** Config_GetStrings(const Config* cfg, uint32_t hash, int32_t& count)
	{
		static List<String> cache;
		static char** cachePtrs = nullptr;
		PurgePtr(cachePtrs);

		cache = cfg -> GetStrings(hash);
		count = cache.Size();
		cachePtrs = GetStringListPtrs(cache);

		return const_cast<const char **>(cachePtrs);
	}


    const Config* Config_GetChildConfigs(const Config* cfg, uint32_t hash, int32_t& numConfigs, int32_t& inc)
    {
    	static List<Config> cache;
    	cache = cfg -> GetChildConfigs(hash);

    	inc = sizeof(Config);
    	numConfigs = cache.Size();
    	return cache.GetArrayPtr();
	}
}