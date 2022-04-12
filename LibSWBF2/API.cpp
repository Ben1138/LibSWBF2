#include "pch.h"
#include "API.h"
#include "InternalHelpers.h"
#include "Types/LibString.h"
#include "Types/Enums.h"
#include "Types/Planning.h"
#include "Chunks/MSH/MSH.h"

#include <string.h>
#include "Container.h"
#include "Wrappers/Wrappers.h"

#include "Chunks/HeaderNames.h"


namespace LibSWBF2
{

#define CheckPtr(obj, ret) if (obj == nullptr) { LOG_ERROR("[API] Given Pointer was NULL!"); return ret; }

	// Helpers
	void GetStringListPtrs(const List<String>& strings, List<const char*>& outPtrs)
	{
		outPtrs.Clear();
		for (int i = 0; i < strings.Size(); i++)
		{
			outPtrs.Add(strings[i].Buffer());
		}
	}


	// Memory //
	void Memory_Blit(void *dest, void *src, int numBytes)
	{
		memcpy(dest, src, numBytes);
	}


	// Hashing //

	uint8_t Hashing_Lookup(uint32_t hash, const char *& str)
	{
		static String lookupCache;
		bool r = FNV::Lookup(hash, lookupCache);
		str = lookupCache.Buffer();
		return r;
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

	uint16_t Container_AddLevel(Container* container, const char *path)
	{
		CheckPtr(container, UINT16_MAX)
		return (uint32_t) container -> AddLevel(path);
	}

	uint16_t Container_AddLevelFiltered(Container* container, const char* path, const char** subLVLs, uint32_t subLVLCount)
	{
		CheckPtr(container, UINT16_MAX)
		CheckPtr(subLVLs, UINT16_MAX)

		List<String> filter;
		for (uint32_t i = 0; i < subLVLCount; ++i)
		{
			filter.Add(subLVLs[i]);
		}

		return (uint32_t)container->AddLevel(path, &filter);
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

	void Container_GetLoadedLevels(Container* container, uint16_t*& handles, uint16_t handleCount)
	{
		CheckPtr(container,);
		static List<uint16_t> HANDLES;
		HANDLES = container->GetLoadedLevels();
		handles = HANDLES.GetArrayPtr();
		handleCount = (uint16_t)HANDLES.Size();
	}

	uint8_t Container_GetStatus(Container* container, uint32_t handle)
	{
		CheckPtr(container, (uint8_t)ELoadStatus::Uninitialized);
		return (uint8_t)container->GetStatus(handle);
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

	const void* Container_GetWrapperFNV(Container* container, uint32_t type, uint32_t name)
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
				return static_cast<const void*>(container-> FindScript(name));
			case 7:
				return static_cast<const void*>(container-> FindSound(name));
			default:
				return nullptr;
		}
	}


	const void* Container_GetWrapper(Container* container, uint32_t type, const char *name)
	{
		return Container_GetWrapperFNV(container, type, (uint32_t) FNV::Hash(name));
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
		return Level_GetWrapperFNV(level, type, (uint32_t) FNV::Hash(name));
	}

	const void* Level_GetWrapperFNV(const Level* level, uint32_t type, uint32_t name)
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
		case 7:
			return static_cast<const void*>(level->GetSound(name));
		case 8:
			return static_cast<const void*>(level->GetLocalization(name));
		case 9:
			return static_cast<const void*>(level->GetAnimationSkeleton(name));
		case 10:
			return static_cast<const void*>(level->GetSoundBank(name));
		case 11:
			return static_cast<const void*>(level->GetSoundStream(name));
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
			numWrappers = (uint32_t)terrains.Size();
			wrapperSize = sizeof(Terrain);
			return static_cast<const void*>(terrains.GetArrayPtr());
		}
		case 1:
		{
			const List<Model>& models = level->GetModels();
			numWrappers = (uint32_t)models.Size();
			wrapperSize = sizeof(Model);
			return static_cast<const void*>(models.GetArrayPtr());
		}
		case 2:
		{
			const List<Texture>& textures = level->GetTextures();
			numWrappers = (uint32_t)textures.Size();
			wrapperSize = sizeof(Texture);
			return static_cast<const void*>(textures.GetArrayPtr());
		}
		case 3:
		{
			const List<World>& worlds = level->GetWorlds();
			numWrappers = (uint32_t)worlds.Size();
			wrapperSize = sizeof(World);
			return static_cast<const void*>(worlds.GetArrayPtr());
		}
		case 4:
		{
			const List<EntityClass>& entityClasses = level->GetEntityClasses();
			numWrappers = (uint32_t)entityClasses.Size();
			wrapperSize = sizeof(EntityClass);
			return static_cast<const void*>(entityClasses.GetArrayPtr());
		}
		case 5:
		{
			const List<AnimationBank>& animationBanks = level->GetAnimationBanks();
			numWrappers = (uint32_t)animationBanks.Size();
			wrapperSize = sizeof(AnimationBank);
			return static_cast<const void*>(animationBanks.GetArrayPtr());
		}
		case 6:
		{
			const List<Script>& scripts = level->GetScripts();
			numWrappers = (uint32_t)scripts.Size();
			wrapperSize = sizeof(Script);
			return static_cast<const void*>(scripts.GetArrayPtr());			
		}
		case 7:
		{
			const List<Sound>& sounds = level->GetSounds();
			numWrappers = (uint32_t)sounds.Size();
			wrapperSize = sizeof(Sound);
			return static_cast<const void*>(sounds.GetArrayPtr());
		}
		case 8:
		{
			const List<Localization>& locals = level->GetLocalizations();
			numWrappers = (uint32_t)locals.Size();
			wrapperSize = sizeof(Localization);
			return static_cast<const void*>(locals.GetArrayPtr());
		}
		case 9:
		{
			const List<AnimationSkeleton>& skels = level->GetAnimationSkeletons();
			numWrappers = (uint32_t)skels.Size();
			wrapperSize = sizeof(AnimationSkeleton);
			return static_cast<const void*>(skels.GetArrayPtr());
		}
		case 10:
		{
			const List<SoundBank>& banks = level->GetSoundBanks();
			numWrappers = (uint32_t)banks.Size();
			wrapperSize = sizeof(SoundBank);
			return static_cast<const void*>(banks.GetArrayPtr());
		}
		case 11:
		{
			const List<SoundStream>& streams = level->GetSoundStreams();
			numWrappers = (uint32_t)streams.Size();
			wrapperSize = sizeof(SoundStream);
			return static_cast<const void*>(streams.GetArrayPtr());
		}
		case 12:
		{
			const List<PlanSet>& planSets = level->GetPlanSets();
			numWrappers = (uint32_t)planSets.Size();
			wrapperSize = sizeof(PlanSet);
			return static_cast<const void*>(planSets.GetArrayPtr());
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
		
		numConfigs = (uint32_t)configs.Size();
		return configs.GetArrayPtr();
	}

	const char* ENUM_TopologyToString(ETopology topology)
	{
		static Types::String lastToString;
		lastToString = TopologyToString(topology);
		return lastToString.Buffer();
	}


	
	//Wrappers - Terrain
	const uint8_t Terrain_FetchSimpleFields(const Terrain* ter, int32_t &numTexes, const char**& texNamesOut,
											float_t& hU, float_t& hL, uint32_t& numVerts, Vector3*& vBuf,
											uint32_t& numNormals, Vector3*& nBuf, uint32_t& numUVs, Vector2*& uvBuf)
	{
		static List<const char*> texNamesPtrs;
		CheckPtr(ter,false);

		const List<String>& texNames = ter -> GetLayerTextures();
        numTexes = (int32_t)texNames.Size();
        GetStringListPtrs(texNames, texNamesPtrs);
        texNamesOut = texNamesPtrs.GetArrayPtr();

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
        										uint32_t& vCount, Vector3*& vBuf, uint32_t& maskFlags, 
        										const char *& namePtr, const char *& nodeNamePtr)
    {
    	CheckPtr(cmPtr, false);
    	
    	static String name;
    	static String nodeName;

    	cmPtr -> GetIndexBuffer(ETopology::TriangleList, iCount, iBuf);
    	cmPtr -> GetVertexBuffer(vCount, vBuf);
    	maskFlags = (uint32_t) cmPtr -> GetMaskFlags();

    	name = cmPtr -> GetName();
    	namePtr = name.Buffer();

    	nodeName = cmPtr -> GetNodeName();
    	nodeNamePtr = nodeName.Buffer();

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
    const uint8_t Segment_FetchAllFields(const Segment* seg, uint8_t& pretx, const char *&boneName, const char *&tag,
														uint32_t& numVerts, Vector3*& pBuf, Vector3*& nBuf, Vector2*&uvBuf,
														uint32_t& numVWs, VertexWeight*& vwBuf,
														int32_t& topo, uint32_t& numInds, uint16_t*& iBuf,
														const Material*& mat)
    {
    	static String boneNameCache;
    	static String tagCache;

    	CheckPtr(seg, false);

    	pretx = seg -> IsPretransformed();
    	
    	boneNameCache = seg -> GetBone();
    	boneName = boneNameCache.Buffer();

    	tagCache = seg -> GetTag();
    	tag = tagCache.Buffer();

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
                    char*& attachedLightName, uint32_t& matFlags, uint32_t& specExp,
                    uint32_t& param1, uint32_t&param2)
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

    	param1 = matPtr -> GetFirstParameter();
    	param2 = matPtr -> GetSecondParameter();

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


	// Wrappers - Barrier
    const void * Barrier_GetFieldPtr(const Barrier* bar, uint8_t fieldID)
    {
    	CheckPtr(bar, nullptr);
    	static Vector4 rotCache;

    	void *fieldPtr = nullptr;
    	switch (fieldID)
    	{
    		case 0:
    			fieldPtr = (void *) &(bar -> GetPosition());
    			break;
    		case 1:
    			rotCache = bar -> GetRotation();
    			fieldPtr = (void *) &rotCache;
    			break;
    		case 2:
    			fieldPtr = (void *) &(bar -> GetFlag());
    			break;
    		case 3:
    			fieldPtr = (void *) bar -> GetName().Buffer();
    			break;
    		case 4:
    			fieldPtr = (void *) &(bar -> GetSize());
    			break;
    		default:
    			break; 
    	}

    	return fieldPtr;
    }

	// Wrappers - HintNode
    const void * HintNode_GetFieldPtr(const HintNode* hnt, uint8_t fieldID)
    {
    	CheckPtr(hnt, nullptr);
    	static Vector4 rotCache;

    	void *fieldPtr = nullptr;
    	switch (fieldID)
    	{
    		case 0:
    			fieldPtr = (void *) &(hnt -> GetPosition());
    			break;
    		case 1:
    			rotCache = hnt -> GetRotation();
    			fieldPtr = (void *) &rotCache;
    			break;
    		case 2:
    			fieldPtr = (void *) &(hnt -> GetType());
    			break;
    		case 3:
    			fieldPtr = (void *) hnt -> GetName().Buffer();
    			break;
    		default:
    			break; 
    	}

    	return fieldPtr;
    }


	const void HintNode_GetProperties(const HintNode* hnt, uint32_t*& hashesBuffer, const char**& valuesBuffer, int32_t& count)
	{
		CheckPtr(hnt,);
		static List<const char*> ptrsBuffer;
		static List<String> values;
		static List<uint32_t> hashes;

		hnt->GetProperties(hashes, values);

		hashesBuffer = hashes.GetArrayPtr();
		count = (int32_t)values.Size();
		GetStringListPtrs(values, ptrsBuffer);
		valuesBuffer = ptrsBuffer.GetArrayPtr();
	}


	//Wrappers - World

	const uint8_t World_FetchAllFields(const World* world, const char*&nameOut, const char*&skyNameOut,
										const Terrain*& terrPtr)
	{
		CheckPtr(world,false);
		static String skyNameCache;

		nameOut = world -> GetName().Buffer();

		skyNameCache = world -> GetSkyName();
		skyNameOut = skyNameCache.Buffer();

		terrPtr = world -> GetTerrain();

		return true;
	}


	const bool World_GetChildrenList(const World* world, uint8_t listID, void *& listPtr, int32_t& listCount, int32_t& wrapperSize)
	{
		CheckPtr(world,false);

		listPtr = nullptr;
		switch (listID)
		{
			case 0:
			{
		    	const List<Instance>& instances = world -> GetInstances();
				listPtr = (void *) instances.GetArrayPtr();
				listCount = (int32_t)instances.Size();
				wrapperSize = sizeof(Instance);
				break;
			}
			case 1:
			{
		    	const List<Region>& regions = world -> GetRegions();
				listPtr = regions.GetArrayPtr();
				listCount = (int32_t)regions.Size();
				wrapperSize = sizeof(Region);
				break;
			}
			case 2:
			{
		    	const List<WorldAnimation>& anims = world -> GetAnimations();
				listPtr = anims.GetArrayPtr();
				listCount = (int32_t)anims.Size();
				wrapperSize = sizeof(WorldAnimation);
				break;
			}
			case 3:
			{
		    	const List<WorldAnimationGroup>& animGroups = world -> GetAnimationGroups();
				listPtr = animGroups.GetArrayPtr();
				listCount = (int32_t)animGroups.Size();
				wrapperSize = sizeof(WorldAnimationGroup);
				break;
			}
			case 4:
			{
		    	const List<WorldAnimationHierarchy>& animHiers = world -> GetAnimationHierarchies();
				listPtr = animHiers.GetArrayPtr();
				listCount = (int32_t)animHiers.Size();
				wrapperSize = sizeof(WorldAnimationHierarchy);
				break;
			}
			case 5:
			{
		    	const List<Barrier>& barriers = world -> GetBarriers();
				listPtr = barriers.GetArrayPtr();
				listCount = (int32_t)barriers.Size();
				wrapperSize = sizeof(Barrier);
				break;
			}
			case 6:
			{
		    	const List<HintNode>& hintNodes = world -> GetHintNodes();
				listPtr = hintNodes.GetArrayPtr();
				listCount = (int32_t)hintNodes.Size();
				wrapperSize = sizeof(HintNode);
				break;
			}
			default:
				break;
		}

		return listPtr != nullptr;
	}



	//Wrappers - World Animation

	const uint8_t WorldAnim_FetchAllFields(const WorldAnimation* anim, uint8_t& loop, uint8_t& localT, const char*& namePtr)
	{
		static String nameCache;
		CheckPtr(anim,false);

		loop = anim -> IsLooping();
		localT = anim -> IsTranslationLocal();

		nameCache = anim -> GetName();
		namePtr = nameCache.Buffer();
		
		return true;
	}

    const void WorldAnim_GetAnimKeys(const WorldAnimation* anim, WorldAnimationKey*& keyBuff, int32_t& numKeys, uint8_t IsRotation)
    {
    	static List<WorldAnimationKey> KeyCache;
    	numKeys = 0;
		CheckPtr(anim,);

		if (IsRotation)
		{
			KeyCache = anim -> GetRotationKeys();
		}
		else 
		{
			KeyCache = anim -> GetPositionKeys();
		}

		keyBuff = KeyCache.GetArrayPtr();
		numKeys = KeyCache.Size();
    }


	//Wrappers - World Animation Group

    const uint8_t WorldAnimGroup_FetchAllFields(const WorldAnimationGroup* group, uint8_t& bool0, uint8_t& bool1, const char*& namePtr)
    {
    	static String nameCache;
    	CheckPtr(group,false);

    	nameCache = group -> GetName();
    	namePtr = nameCache.Buffer();

    	bool0 = group -> IsPlayingAtStart();
    	bool1 = group -> DisablesHierarchies();

    	return true;
    }

    const void WorldAnimGroup_GetAnimInstPairs(const WorldAnimationGroup* group, const char**& animNames, const char**& instNames, int32_t& numPairs)
    {
    	static List<String> animsCache;
    	static List<String> instsCache;
    	static List<const char*> animsPtrsBuffer;
    	static List<const char*> instsPtrsBuffer;

    	numPairs = 0;
    	CheckPtr(group,);

    	group -> GetAnimationInstancePairs(animsCache, instsCache);

		numPairs = (int32_t)animsCache.Size();

		GetStringListPtrs(animsCache, animsPtrsBuffer);
		GetStringListPtrs(instsCache, instsPtrsBuffer);
		
		animNames = animsPtrsBuffer.GetArrayPtr();
		instNames = instsPtrsBuffer.GetArrayPtr();
    }


    const uint8_t WorldAnimHier_FetchAllFields(const WorldAnimationHierarchy* hier, const char *& rootPtr, const char**& childNames, int32_t& numChildren)
    {
    	static String rootCache;
    	static List<String> childrenCache;
    	static List<const char*> childPtrsBuffer;
    	CheckPtr(hier,false);

    	rootCache = hier -> GetRootName();
    	rootPtr = rootCache.Buffer();

    	childrenCache = hier -> GetChildNames();
    	GetStringListPtrs(childrenCache, childPtrsBuffer);

    	childNames = childPtrsBuffer.GetArrayPtr();
    	numChildren = childrenCache.Size();

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
    const uint8_t Instance_FetchSimpleFields(const Instance* instPtr, const char*& name, Vector4*& rot, Vector3*& pos, const char*& ecName, const EntityClass*& ec)
    {
    	static Vector4 rotCache;
    	static Vector3 posCache;
    	CheckPtr(instPtr,false);

    	name = instPtr -> GetName().Buffer();
    	ecName = instPtr -> GetEntityClassName().Buffer();
		ec = instPtr -> GetEntityClass();

    	rotCache = instPtr -> GetRotation();
    	posCache = instPtr -> GetPosition();

    	rot = &rotCache;
    	pos = &posCache;

    	return true;
    }

	template<class T1, class T2>
	uint8_t GenericGetProperty(const T1* ptr, T2 prop, const char*& value)
	{
		CheckPtr(ptr, false);
		static String propValue;
		if (ptr->GetProperty(prop, propValue))
		{
			value = propValue.Buffer();
			return true;
		}
		value = nullptr;
		return false;
	}

	template<class T1, class T2>
	uint8_t GenericGetProperties(const T1* ptr, T2 prop, const char**& values, uint32_t& count)
	{
		CheckPtr(ptr, false);
		static List<String> propValues;
		static List<const char*> propValuePtrs;
		propValues.Clear();
		propValuePtrs.Clear();
		if (ptr->GetProperty(prop, propValues))
		{
			GetStringListPtrs(propValues, propValuePtrs);
			values = propValuePtrs.GetArrayPtr();
			count  = (uint32_t)propValuePtrs.Size();
			return true;
		}
		values = nullptr;
		count = 0;
		return false;
	}

	uint8_t Instance_GetPropertyFromName(const Instance* instPtr, const char* propName, const char*& value)
	{
		return GenericGetProperty(instPtr, propName, value);
	}

	uint8_t Instance_GetPropertyFromHash(const Instance* instPtr, uint32_t hashedPropName, const char*& value)
	{
		return GenericGetProperty(instPtr, hashedPropName, value);
	}

	uint8_t Instance_GetPropertiesFromName(const Instance* instPtr, const char* propName, const char**& values, uint32_t& count)
	{
		return GenericGetProperties(instPtr, propName, values, count);
	}

	uint8_t Instance_GetPropertiesFromHash(const Instance* instPtr, uint32_t hashedPropName, const char**& values, uint32_t& count)
	{
		return GenericGetProperties(instPtr, hashedPropName, values, count);
	}

    void Instance_GetOverriddenProperties(const Instance *instPtr, uint32_t*& hashesBuffer, const char**& valuesBuffer, int32_t& count)
    {
    	CheckPtr(instPtr,)
    	static List<String> values;
    	static List<uint32_t> hashes;
    	static List<const char*> ptrsBuffer;

		instPtr->GetOverriddenProperties(hashes, values);
    	hashesBuffer = hashes.GetArrayPtr();
    	count = (int32_t)values.Size();
		GetStringListPtrs(values, ptrsBuffer);
    	valuesBuffer = ptrsBuffer.GetArrayPtr();
    }


    //Wrappers - EntityClass
	void EntityClass_FetchAllFields(const EntityClass* ec, const char*& name, uint8_t& classType, const EntityClass*& baseClass, const char*& baseClassName)
	{
		CheckPtr(ec, );
		name = ec->GetTypeName().Buffer();
		classType = (uint8_t)ec->GetClassType();
		baseClass = ec->GetBase();
		baseClassName = ec->GetBaseName().Buffer();
	}

	uint8_t EntityClass_GetPropertyFromName(const EntityClass* ec, const char* propName, const char*& value)
	{
		return GenericGetProperty(ec, propName, value);
	}

	uint8_t EntityClass_GetPropertyFromHash(const EntityClass* ec, uint32_t hashedPropName, const char*& value)
	{
		return GenericGetProperty(ec, hashedPropName, value);
	}

	uint8_t EntityClass_GetPropertiesFromName(const EntityClass* ec, const char* propName, const char**& values, uint32_t& count)
	{
		return GenericGetProperties(ec, propName, values, count);
	}

	uint8_t EntityClass_GetPropertiesFromHash(const EntityClass* ec, uint32_t hashedPropName, const char**& values, uint32_t& count)
	{
		return GenericGetProperties(ec, hashedPropName, values, count);
	}


    const char *EntityClass_GetName(const EntityClass *ec)
    {
    	CheckPtr(ec,"")
    	static String typeName;

    	typeName = ec -> GetTypeName();
    	return typeName.Buffer();     	
    }

	const EntityClass* EntityClass_GetBase(const EntityClass* ec)
	{
		CheckPtr(ec, nullptr)
		return ec->GetBase();
	}

    const char *EntityClass_GetBaseName(const EntityClass *ec)
    {
    	CheckPtr(ec,"")
    	static String baseName;

    	baseName = ec -> GetBaseName();
    	return baseName.Buffer(); 
    }


    void EntityClass_GetOverriddenProperties(const EntityClass *ec, uint32_t*& hashesBuffer, const char**& valuesBuffer, int32_t& count)
    {
    	CheckPtr(ec,)
    	static List<const char*> ptrsBuffer;
    	static List<String> values;
    	static List<uint32_t> hashes;

		ec->GetOverriddenProperties(hashes, values);
    	
		hashesBuffer = hashes.GetArrayPtr();
		count = (int32_t)values.Size();
		GetStringListPtrs(values, ptrsBuffer);
		valuesBuffer = ptrsBuffer.GetArrayPtr();
    }
   
	void EntityClass_GetAllProperties(const EntityClass* ec, uint32_t*& hashesBuffer, const char**& valuesBuffer, int32_t& count)
	{
		CheckPtr(ec,)
		static List<const char*> ptrsBuffer;
		static List<String> values;
		static List<uint32_t> hashes;

		ec->GetAllProperties(hashes, values);

		hashesBuffer = hashes.GetArrayPtr();
		count = (int32_t)values.Size();
		GetStringListPtrs(values, ptrsBuffer);
		valuesBuffer = ptrsBuffer.GetArrayPtr();
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

    	crcs = setPtr -> GetAnimations();
    	
    	numCRCs = (int32_t)crcs.Size();
    	return crcs.GetArrayPtr();
    }

	const uint32_t* AnimationBank_GetBoneCRCs(const AnimationBank* setPtr, uint32_t animCRC, int& numCRCs)
	{
		static List<uint32_t> crcs;

		numCRCs = 0;
		CheckPtr(setPtr, nullptr);

		crcs = setPtr->GetBones(animCRC);

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


    // Wrappers - AnimationSkeleton
    const char* AnimationSkeleton_GetName(const AnimationSkeleton* skelPtr)
    {
    	static String nameCache;
    	CheckPtr(skelPtr, nullptr);
    	nameCache = skelPtr -> GetName();

    	return nameCache.Buffer();
    }

    const uint8_t AnimationSkeleton_GetJoints(const AnimationSkeleton* skelPtr, int32_t& numJoints, Joint*& jointsPtr)
    {
    	static List<Joint> jointsCache;
    	CheckPtr(skelPtr, false);

    	if (skelPtr -> GetJoints(jointsCache))
    	{
    		numJoints = (int32_t) jointsCache.Size();
    		jointsPtr = jointsCache.GetArrayPtr();
    		return true;
    	}
    	else 
    	{
    		numJoints = 0;
    		return false;
    	}
    }


    // Wrappers - Sound
	const char* Sound_GetName(const Sound* sound)
	{
		CheckPtr(sound, nullptr);
		static String name;
		name = sound->GetName();
		return name.Buffer();
	}

	const uint8_t Sound_FetchAllFields(const Sound *sound, 
		uint32_t& nameOut, uint32_t& sampleRate, 
		uint32_t& sampleCount, uint8_t& blockAlign,
		uint8_t& hasDataOut)
    {
    	CheckPtr(sound, false);
    	nameOut = sound -> GetHashedName();
    	return true;
    }

	uint8_t Sound_GetData(const Sound* sound, uint32_t& sampleRate, uint32_t& sampleCount, uint8_t& blockAlign, const uint8_t*& data)
	{
		CheckPtr(sound, false);
		return (uint8_t)sound->GetData(sampleRate, sampleCount, blockAlign, data);
	}



	// Wrappers - SoundStream
    const uint8_t SoundStream_FetchAllFields(const SoundStream *str, 
     		uint32_t& nameOut, uint8_t& hasDataOut,
    		uint32_t& formatOut, uint32_t& numChannelsOut)
    {
		CheckPtr(str, false);
		hasDataOut = str -> HasData();
		formatOut = (uint32_t) str -> GetFormat();
		nameOut = str -> GetHashedName();
		numChannelsOut = str -> GetNumChannels();
		return true;
    }

    const uint8_t SoundStream_GetSound(const SoundStream *str, uint32_t soundName, const Sound*& soundOut)
    {
		CheckPtr(str, false);
		soundOut = str -> GetSound(soundName);
		return soundOut != nullptr; 
    }

    const uint8_t SoundStream_GetSounds(const SoundStream *str, const Sound*& soundsOut, uint32_t& numSounds, uint32_t& soundInc)
    {
		CheckPtr(str, false);
		const List<Sound>& sounds = str -> GetSounds();
		soundsOut = sounds.GetArrayPtr();
		numSounds = sounds.Size();
		soundInc = sizeof(Sound);
		return numSounds > 0;
    }

		
	// Wrappers - SoundBank
    const uint8_t SoundBank_FetchAllFields(const SoundBank *bnk, 
    	uint32_t& nameOut, uint8_t& hasDataOut, uint32_t& formatOut)
    {
		CheckPtr(bnk, false);
		hasDataOut = bnk -> HasData();
		formatOut = (uint32_t) bnk -> GetFormat();
		nameOut = bnk -> GetHashedName();
		return true;
    }

    const uint8_t SoundBank_GetSound(const SoundBank *bnk, uint32_t soundName, const Sound*& soundOut)
    {
		CheckPtr(bnk, false);
		soundOut = bnk -> GetSound(soundName);
		return soundOut != nullptr; 
    }

    const uint8_t SoundBank_GetSounds(const SoundBank *bnk, const Sound*& soundsOut, uint32_t& numSounds, uint32_t& soundInc)
    {
		CheckPtr(bnk, false);
		const List<Sound>& sounds = bnk -> GetSounds();
		soundsOut = sounds.GetArrayPtr();
		numSounds = sounds.Size();
		soundInc = sizeof(Sound);
		return numSounds > 0;
    }



	const char* Localization_GetName(const Localization* local)
	{
		CheckPtr(local, nullptr);
		return local->GetName().Buffer();
	}

	uint8_t Localization_GetLocalizedWideString(const Localization* local, const char* path, uint16_t*& chars, uint32_t& count)
	{
		CheckPtr(local, false);
		return (uint8_t)local->GetLocalizedWideString(path, chars, count);
	}


    // Config stuff

    const uint8_t Field_FetchAllFields(const Field *cfg, Scope*& scop)
    {
    	CheckPtr(cfg,false);
    	scop = const_cast<Scope *>(&(cfg->m_Scope));
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

    	count = (uint32_t)cache.Size();
    	return cache.GetArrayPtr();
    }


    const uint8_t Config_FetchSimpleFields(const Config* cfg, uint32_t& name)
    {
    	CheckPtr(cfg,false);
    	name = cfg -> m_Name;
    	return true;
    }

	const uint32_t Field_GetNameHash(const Field* cfg)
	{
		return cfg->GetNameHash();
	}

	const uint8_t Field_GetNumValues(const Field* cfg)
	{
		return cfg->GetNumValues();
	}

	const float_t Field_GetFloat(const Field* cfg, uint8_t index)
	{
		return cfg->GetFloat(index);
	}

    const uint32_t Field_GetUInt32(const Field* cfg, uint8_t index)
    {
		return cfg->GetUInt32(index);    	
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

	const char* Field_GetString(const Field* cfg, uint8_t index)
	{
		static String cache;
		cache = cfg->GetString(index);
		return cache.Buffer(); 
	}

	const char* Field_GetName(const Field* cfg)
	{
		static String cache;
		cache = cfg->GetName();
		return cache.Buffer();
	}


	// PlanSet //
    const uint8_t PlanSet_GetChildWrappers(const PlanSet* ps, uint8_t id, void*& listPtr, int32_t& listSize, int32_t& elSize)
    {
    	CheckPtr(ps,false);

    	listSize = 0;
    	listPtr = nullptr;
    	switch (id)
    	{
    		case 0:
    		{
    			const List<Hub>& hubs = ps -> GetHubs();
    			listPtr = (void *) hubs.GetArrayPtr();
    			listSize = hubs.Size();
    			elSize = (int32_t) sizeof(Hub);
    			break;
    		}
    		case 1:
    		{
    			const List<Connection>& cons = ps -> GetConnections();
    			listPtr = (void *) cons.GetArrayPtr();
    			listSize = cons.Size();
    			elSize = (int32_t) sizeof(Connection);
    			break;
    		}
    		default:
    			return false;
    	}

    	return listPtr != nullptr;
    }        
    

    // Hub //
    const void * Hub_GetFieldPtr(const Hub* hub, uint8_t id, int32_t& numBytes)
    {
    	CheckPtr(hub,nullptr);
    	switch (id)
    	{
    		case 0:
    		    return (void *) hub -> m_Name.Buffer();
    		case 1:
    			return (void *) &(hub -> m_Position);
    		case 2:
    			return (void *) &(hub -> m_Radius);
    		case 3:
    			return (void *) hub -> m_ConnectionIndices;
    		case 4:
    			return (void *) hub -> m_ConnectionsPerLayer;
    		case 5:
    		{
 				numBytes = (int32_t) hub -> m_QuantizedDataBuffer.Size();
    			return (void *) hub -> m_QuantizedDataBuffer.GetArrayPtr();
    		}
    		default:
    			return nullptr;
    	}
    }      

    // Connection //
    const void * Connection_GetFieldPtr(const Connection* con, uint8_t id)
    {
    	CheckPtr(con,nullptr);
    	switch (id)
    	{
    		case 0:
    			return (void *) con -> m_Name.Buffer();
    		case 1:
    			return (void *) &(con -> m_Start);
    		case 2:
    			return (void *) &(con -> m_End);
    		case 3:
    			return (void *) &(con -> m_FilterFlags);
    		case 4:
    			return (void *) &(con -> m_AttributeFlags);
    		default:
    			return nullptr;
    	}
    }







}