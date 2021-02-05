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

#include <iostream>
#include <string>



namespace LibSWBF2
{
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
				return static_cast<const void *>(container -> FindLight(name));
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


	void Level_GetLights(const Level* level, const Light**& LightArr, uint32_t& LightCount)
	{
		CheckPtr(level, );
		const List<Light>& Lights = level->GetLights();

		// since level->GetModels() just returns a reference to the actual list
		// member of level, which will persist even after this call ended, we can safely
		// provide the model addresses of the underlying buffer to the inquirer.
		// The inquirer of course is not allowed to alter the data!
		static List<const Light*> LightPtrs;
		LightPtrs.Clear();

		for (size_t i = 0; i < Lights.Size(); ++i)
		{
			LightPtrs.Add(&Lights[i]);
		}

		LightArr = LightPtrs.GetArrayPtr();
		LightCount = (uint32_t) LightPtrs.Size();
	}


	const Light* Level_GetLight(const Level* level, const char* lightName)
	{
		CheckPtr(level, nullptr);
		return level->GetLight(lightName);
	}


	bool Level_GetGlobalLighting(const Level* level, Vector3 *& topColor, Vector3 *& bottomColor, 
								const char*& light1Name, const char*& light2Name)
	{
		const auto* config = level -> GetGlobalLighting();
		static Vector3 topCol, bottomCol;
		static String name1, name2;

		if (config != nullptr)
		{	
			topColor    = config -> GetTopColor(topCol) ? &topCol : nullptr;
			bottomColor = config -> GetBottomColor(bottomCol) ? &bottomCol : nullptr;

			light1Name  = config -> GetLight1(name1) ? name1.Buffer() : "";
			light2Name  = config -> GetLight2(name2) ? name2.Buffer() : "";

			return true;
		}

		return false;
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
    	delete[] imageDataCache;
    	imageDataCache = nullptr;

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


	const char* ENUM_TopologyToString(ETopology topology)
	{
		static Types::String lastToString;
		lastToString = TopologyToString(topology);
		return lastToString.Buffer();
	}


	
	//Wrappers - Terrain

	const void Terrain_GetTexNames(const Terrain *tern, uint32_t& numTextures, char**& namesOut)
	{
		static char** nameStrings = nullptr;
		delete[] nameStrings; 
		nameStrings = nullptr;

		numTextures = 0;
		CheckPtr(tern, );

        const List<String>& texNames = tern -> GetLayerTextures();
        numTextures = (uint32_t) texNames.Size();
        nameStrings = GetStringListPtrs(texNames);
        namesOut = nameStrings;
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


	const void Terrain_GetHeightBounds(const Terrain *ter, float& floor, float& ceiling)
	{
    	CheckPtr(ter, );
		ter -> GetHeightBounds(floor, ceiling);
	}


	const void Terrain_GetVertexBuffer(const Terrain *terr, float_t*& positions, int32_t& numVerts)
	{
		static float_t *rawBuffer = nullptr;

		numVerts = 0;
		CheckPtr(terr,)

		delete rawBuffer;

		Vector3 *positionsBuf;
		uint32_t numBufVerts;

		terr -> GetVertexBuffer(numBufVerts, positionsBuf);

		rawBuffer = new float_t[numBufVerts * 3];

		numVerts = (int32_t) numBufVerts;

		for (int32_t i = 0; i < numVerts * 3; i+=3)
		{
			Vector3& cur = positionsBuf[i / 3];
			rawBuffer[i] = cur.m_X;
			rawBuffer[i+1] = cur.m_Y;
			rawBuffer[i+2] = cur.m_Z;
		}

		positions = rawBuffer;
	}


	const void Terrain_GetNormalsBuffer(const Terrain *ter, float_t*& normals, int32_t& numNormals)
	{
		static float_t *rawBuffer = nullptr;

		numNormals = 0;
		CheckPtr(ter,)

		delete rawBuffer;

		Vector3 *normalsBuf;
		uint32_t numBufVerts;

		ter -> GetNormalBuffer(numBufVerts, normalsBuf);

		rawBuffer = new float_t[numBufVerts * 3];

		numNormals = (int32_t) numBufVerts;

		for (int32_t i = 0; i < numNormals * 3; i+=3)
		{
			Vector3& cur = normalsBuf[i / 3];
			rawBuffer[i] = cur.m_X;
			rawBuffer[i+1] = cur.m_Y;
			rawBuffer[i+2] = cur.m_Z;
		}

		normals = rawBuffer;
	}

	const void Terrain_GetIndexBuffer(const Terrain *terr, uint32_t*& indicies, int32_t& numIndsOut)
	{
		numIndsOut = 0;
		CheckPtr(terr,)

		indicies = nullptr;
		uint32_t numInds = 0;

		terr -> GetIndexBuffer(ETopology::TriangleList, numInds, indicies);
		numIndsOut = numInds;
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
                    char* attachedLightName, uint32_t& matFlags, uint32_t& specExp)
    {	
    	static Vector3 specCache, diffCache;
    	static char** texNamePtrsCache = new char*[4];
    	static String namesCache[4];
    	static char* attachedLightNameCache = nullptr;

    	CheckPtr(matPtr, false);

    	uint8_t count = 0;
    	while (count < 4 && matPtr -> GetTextureName(count, namesCache[count]))
    	{
    		texNamePtrsCache[count] = const_cast<char *>(namesCache[count].Buffer());
    		count++;
    	}
    	numTexes = count;
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
	const uint8_t World_FetchAllFields(const World* world, const char*nameOut, const char*skyNameOut,
										const Light*& lightArr, int32_t& lightCount, int32_t& lightInc,
										const Instance*& instanceArr, int32_t& instCount, int32_t& instInc,
										const Terrain*& terrPtr)
	{
		CheckPtr(world,false);
		static String skyNameCache;

		nameOut = world -> GetName().Buffer();

		skyNameCache = world -> GetSkyName();
		skyNameOut = skyNameCache.Buffer();

		const List<Light>& lights = world -> GetLights();
    	lightArr = lights.GetArrayPtr();
    	lightCount = lights.Size();
    	lightInc = sizeof(Light);

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

    	delete[] ptrsBuffer;

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

    	delete[] ptrsBuffer;

    	if (!ec -> GetOverriddenProperties(hashes, values)){ return false; }
    	
		hashesBuffer = hashes.GetArrayPtr();
		count = values.Size();
		ptrsBuffer = GetStringListPtrs(values);
		valuesBuffer = ptrsBuffer;
		return true;
    }


    const char* Light_GetAllFields(const Light* lightPtr, Vector4*& rotPtr,
                                    Vector3*& posPtr, uint32_t& lightType, 
                                    Vector3*& colPtr, float_t& range,
                                    Vector2*& conePtr)
    {
    	CheckPtr(lightPtr, nullptr);

    	static Vector3 lastPos, lastCol;
    	static Vector4 lastRot; 
    	static Vector2 lastCone(0,0);	
    	float_t inner=0,outer=0;

    	lastRot  = lightPtr -> GetRotation();
    	lastPos  = lightPtr -> GetPosition();
    	lastCol  = lightPtr -> GetColor();

    	lightPtr -> GetSpotAngles(inner,outer);
    	lastCone = Vector2(inner,outer);

    	lightType = (uint32_t) lightPtr -> GetType();
    	lightPtr -> GetRange(range);

    	rotPtr  = &lastRot;
    	colPtr  = &lastCol;
    	posPtr  = &lastPos;
    	conePtr = &lastCone;

    	const String& name = lightPtr -> GetName();
    	return name.Buffer();
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
}