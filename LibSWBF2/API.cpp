#include "stdafx.h"
#include "API.h"
#include "InternalHelpers.h"
#include "Types/LibString.h"
#include "Chunks/MSH/MSH.h"

#include <string.h>
#include "Container.h"
#include "Wrappers/Wrappers.h"

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
		CheckPtr(container, UINT32_MAX)
		return (uint32_t) container -> AddLevel(path);
	}

	uint32_t Container_AddLevelFiltered(Container* container, const char* path, const char** subLVLs, uint32_t subLVLCount)
	{
		CheckPtr(container, UINT32_MAX)
		CheckPtr(subLVLs, UINT32_MAX)

		List<String> filter;
		for (uint32_t i = 0; i < subLVLCount; ++i)
		{
			filter.Add(subLVLs[i]);
		}

		return (uint32_t)container->AddLevel(path, &filter);
	}

	uint32_t Container_AddSoundBank(Container* container, const char* path)
	{
		CheckPtr(container, UINT32_MAX)
		return container->AddSoundBank(path);
	}

	void Container_FreeAll(Container* container, uint8_t force)
	{
		CheckPtr(container,)
		container->FreeAll((bool)force);
	}

	float_t Container_GetProgress(Container* container, uint32_t handleNum)
	{
		CheckPtr(container, -1.0f)
		return container -> GetLevelProgress((uint16_t) handleNum);
	}  

	float_t Container_GetOverallProgress(Container* container)
	{
		CheckPtr(container, -1.0f)
		return container->GetOverallProgress();
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
    wrapperMap[typeof(Script)]        = 6;
	*/

	const void* Container_GetWrapper(Container* container, uint32_t type, const char *name)
	{
		switch (type)
		{
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
			case 6:
				return static_cast<const void*>(container->FindScript(name));
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


	const void* Level_GetWrapper(const Level* level, uint32_t type, const char* name)
	{
		CheckPtr(level, nullptr);

		switch (type)
		{
		case 0:
			return static_cast<const void*>(level->GetTerrain(name));
		case 1:
			return static_cast<const void*>(level->GetModel(name));
		case 2:
			return static_cast<const void*>(level->GetTexture(name));
		case 3:
			return static_cast<const void*>(level->GetWorld(name));
		case 4:
			return static_cast<const void*>(level->GetEntityClass(name));
		case 5:
			return static_cast<const void*>(level->GetAnimationBank(name));
		case 6:
			return static_cast<const void*>(level->GetScript(name));
		default:
			return nullptr;
		}
	}

	const void* Level_GetWrappers(const Level* level, uint32_t type, uint32_t& numWrappers, uint32_t& wrapperSize)
	{
		numWrappers = 0;
		wrapperSize = 0;
		CheckPtr(level, nullptr);

		switch (type)
		{
		case 0:
		{
			const List<Terrain>& terrains = level->GetTerrains();
			numWrappers = terrains.Size();
			wrapperSize = sizeof(Terrain);
			return static_cast<const void*>(terrains.GetArrayPtr());
		}
		case 1:
		{
			const List<Model>& models = level->GetModels();
			numWrappers = models.Size();
			wrapperSize = sizeof(Model);
			return static_cast<const void*>(models.GetArrayPtr());
		}
		case 2:
		{
			const List<Texture>& textures = level->GetTextures();
			numWrappers = textures.Size();
			wrapperSize = sizeof(Texture);
			return static_cast<const void*>(textures.GetArrayPtr());
		}
		case 3:
		{
			const List<World>& worlds = level->GetWorlds();
			numWrappers = worlds.Size();
			wrapperSize = sizeof(World);
			return static_cast<const void*>(worlds.GetArrayPtr());
		}
		case 4:
		{
			const List<EntityClass>& entityClasses = level->GetEntityClasses();
			numWrappers = entityClasses.Size();
			wrapperSize = sizeof(EntityClass);
			return static_cast<const void*>(entityClasses.GetArrayPtr());
		}
		case 5:
		{
			const List<AnimationBank>& animationBanks = level->GetAnimationBanks();
			numWrappers = animationBanks.Size();
			wrapperSize = sizeof(AnimationBank);
			return static_cast<const void*>(animationBanks.GetArrayPtr());
		}
		case 6:
		{
			const List<Script>& scripts = level->GetScripts();
			numWrappers = scripts.Size();
			wrapperSize = sizeof(Script);
			return static_cast<const void*>(scripts.GetArrayPtr());			
		}
		default:
			return nullptr;
		}
	}


	const char* Level_GetName(const Level* level)
	{
		static String cache;
		CheckPtr(level, nullptr);
		cache = level -> GetLevelName();
		return cache.Buffer();
	}


	const char* Level_GetPath(const Level* level)
	{
		static String cache;
		CheckPtr(level, nullptr);
		cache = level->GetLevelPath();
		return cache.Buffer();
	}




	//Wrappers - Texture

	const uint8_t Texture_FetchAllFields(const Texture* tex, uint16_t& w, uint16_t& h, const uint8_t*& bufOut, const char*& nameOut)
	{
		static String nameCache;

		CheckPtr(tex,false);

		nameCache = tex -> GetName();
		nameOut = nameCache.Buffer();
	    return tex -> GetImageData(ETextureFormat::R8_G8_B8_A8, 0, w, h, bufOut);    
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
        numTexes = (int32_t)texNames.Size();
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
		segCount = (int32_t)segs.Size();
		segInc = sizeof(Segment);

		boneCount = 0;
		if (model -> GetSkeleton(boneCache)){ boneCount = (int32_t)boneCache.Size(); }
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


	//Wrappers - Region

	const uint8_t Region_FetchAllFields(const Region* regPtr, const Vector3*& sizeOut, 
									 const Vector3*& posOut, const Vector4*& rotOut,
									 const char *&nameOut, const char*& typeOut)
	{
		CheckPtr(regPtr,false);
		static Vector4 rotCache;

		sizeOut = &(regPtr -> GetSize());
		posOut = &(regPtr -> GetPosition());
		
		rotCache = regPtr -> GetRotation();
		rotOut = &rotCache;

		nameOut = regPtr -> GetName().Buffer();
		typeOut = regPtr -> GetType().Buffer();

		return true;
	}


	//Wrappers - World

	const uint8_t World_FetchAllFields(const World* world, const char*&nameOut, const char*&skyNameOut,
										const Instance*& instanceArr, int32_t& instCount, int32_t& instInc,
										const Region*& regionArr, int32_t& regCount, int32_t& regInc,
										const Terrain*& terrPtr)
	{
		CheckPtr(world,false);
		static String skyNameCache;

		nameOut = world -> GetName().Buffer();

		skyNameCache = world -> GetSkyName();
		skyNameOut = skyNameCache.Buffer();

    	const List<Instance>& instances = world -> GetInstances();
		instanceArr = instances.GetArrayPtr();
		instCount = (int32_t)instances.Size();
		instInc = sizeof(Instance);

    	const List<Region>& regions = world -> GetRegions();
		regionArr = regions.GetArrayPtr();
		regCount = (int32_t)regions.Size();
		regInc = sizeof(Region);

		terrPtr = world -> GetTerrain();

		return true;
	}

    
	// Wrappers - Script
	LIBSWBF2_API const char* Script_GetName(const Script* script)
	{
		CheckPtr(script, nullptr);
		static String nameCache;
		nameCache = script->GetName();
		return nameCache.Buffer();
	}

	LIBSWBF2_API uint8_t Script_GetData(const Script* script, const uint8_t*& data, uint32_t& size)
	{
		CheckPtr(script, false);
		size_t sz;
		uint8_t res = (uint8_t)script->GetData(data, sz);
		size = (uint32_t)sz;
		return res;
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
    		count = (int32_t)values.Size();
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
		count = (int32_t)values.Size();
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
			numKeys = (int32_t)values.Size();
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
    	
    	numCRCs = (int32_t)crcs.Size();
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



    // Config stuff

    const uint8_t Field_FetchAllFields(const Field *cfg, Scope*& scop, uint32_t& hash)
    {
    	CheckPtr(cfg,false);
    	scop = const_cast<Scope *>(&(cfg -> scope));
    	hash = cfg -> name;
    	return true;
    }

    const Field** ConfigScope_GetFields(void *ptr, uint32_t hash, uint8_t isScope, uint32_t& count)
    {
    	static List<const Field *> cache;
    	if (isScope)
    	{
    		cache = ((Scope *) ptr) -> GetFields(hash);
    	}
    	else 
    	{
    		cache = ((Config *) ptr) -> GetFields(hash);    		
    	}

    	count = cache.Size();
    	return cache.GetArrayPtr();
    }


    const uint8_t Config_FetchSimpleFields(const Config* cfg, uint32_t& name)
    {
    	CheckPtr(cfg,false);
    	name = cfg -> m_Name;
    	return true;
    }


	const float_t Field_GetFloat(const Field* cfg)
	{
		return cfg -> GetFloat();
	}

	const Vector2* Field_GetVec2(const Field* cfg)
	{
		static Vector2 cache;
		cache = cfg -> GetVector2();
		return &cache; 
	}

	const Vector3* Field_GetVec3(const Field* cfg)
	{
		static Vector3 cache;
		cache = cfg -> GetVector3();
		return &cache; 
	}

	const Vector4* Field_GetVec4(const Field* cfg)
	{
		static Vector4 cache;
		cache = cfg -> GetVector4();
		return &cache; 
	}

	const char* Field_GetString(const Field* cfg)
	{
		static String cache;
		cache = cfg -> GetString();
		return cache.Buffer(); 
	}
}