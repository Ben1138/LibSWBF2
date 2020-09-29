#include "stdafx.h"
#include "API.h"
#include "InternalHelpers.h"
#include "Types/LibString.h"
#include "Chunks/MSH/MSH.h"
#include "Wrappers/Level.h"
#include "Container.h"

namespace LibSWBF2
{
#define CheckPtr(obj, ret) if (obj == nullptr) { LOG_ERROR("[API] Given Pointer was NULL!"); return ret; }

	// Logging //
	void LOG_SetCallbackMethod(const LogCallback Callback)
	{
		CheckPtr(Callback,)
		Logging::Logger::SetLogCallback(Callback);
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
		SWBF2Handle handle = (uint16_t) handleNum;
		return container -> GetLevelProgress(handle);
	}  

	const Level* Container_GetLevel(Container* container, uint32_t handleNum)
	{
		SWBF2Handle handle = (uint16_t) handleNum;
		return container -> GetLevel(handle);
	}

	const void Container_LoadLevels(Container* container)
	{
		container -> StartLoading();
	}

	const void* Container_GetWrapper(Container* container, uint32_t type, const char *name)
	{
		switch (type)
		{
			case 0:
				return static_cast<const void *>(container -> FindModel(name));
			case 1:
				return static_cast<const void *>(container -> FindTexture(name));
			case 2:
				return static_cast<const void *>(container -> FindWorld(name));
			case 3:
				return static_cast<const void *>(container -> FindEntityClass(name));
			case 4:
				return static_cast<const void *>(container -> FindTerrain(name));
			default:
				return nullptr;
		}
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

	void Level_GetModels(const Level* level, const Model**& modelArr, uint32_t& modelCount)
	{
		CheckPtr(level, );
		const List<Model>& models = level->GetModels();

		// since level->GetModels() just returns a reference to the actual list
		// member of level, which will persist even after this call ended, we can safely
		// provide the model addresses of the underlying buffer to the inquirer. 
		// The inquirer of course is not allowed to alter the data!
		static List<const Model*> modelPtrs;
		modelPtrs.Clear();

		for (size_t i = 0; i < models.Size(); ++i)
		{
			modelPtrs.Add(&models[i]);
		}

		modelArr = modelPtrs.GetArrayPtr();
		modelCount = (uint32_t)modelPtrs.Size();
	}

	const char* Model_GetName(const Model* model)
	{
		CheckPtr(model, nullptr);

		// model->GetName() returns a ref to the persistent member,
		// char buffers of String's are always null terminated, so we
		// can just return the buffer pointer.
		const String& name = model->GetName();
		return name.Buffer();
	}

	const void Model_GetSegments(const Model* model, Segment*& segmentArr, uint32_t& segmentCount)
	{
		CheckPtr(model,);
		const List<Segment>& segments = model->GetSegments();
		segmentArr = segments.GetArrayPtr();
		segmentCount = (uint32_t)segments.Size();
	}

	uint8_t Model_IsSkeletalMesh(const Model* model)
	{
		CheckPtr(model, false);
		return model->IsSkeletalMesh();
	}

	uint8_t Model_GetSkeleton(const Model* model, Bone*& boneArr, uint32_t& boneCount)
	{
		CheckPtr(model, false);

		// keep this static, so the buffer is valid after the call ends.
		// this of course results in holding a permanent copy of the last queried
		// bone list in memory, and will overwrite the buffer in the next query...
		// TODO: maybe make the bone list a member of Model?
		static List<Bone> bones;
		if (!model->GetSkeleton(bones))
		{
			return false;
		}
		boneArr = bones.GetArrayPtr();
		boneCount = (uint32_t)bones.Size();
		return true;
	}


	const CollisionMesh* Model_GetCollisionMesh(const Model *model)
	{
		const CollisionMesh& mesh = model -> GetCollisionMesh();
		return &mesh;
	}


	const Model* Level_GetModel(const Level* level, const char* modelName)
	{
		CheckPtr(level, nullptr);
		return level->GetModel(modelName);
	}


	const void CollisionMesh_GetIndexBuffer(const CollisionMesh *collMesh, uint32_t& count, int*& outBuffer)
	{
		static int* tempBuffer = nullptr;
		delete tempBuffer;

		uint32_t* meshBuffer;

		collMesh -> GetIndexBuffer(ETopology::TriangleList, count, meshBuffer);

		tempBuffer = new int[count];

		for (int i = 0; i < (int)count; i++)
		{
			tempBuffer[i] = (int) meshBuffer[i];
		}

		outBuffer = tempBuffer;
	}
    

    const void CollisionMesh_GetVertexBuffer(const CollisionMesh *collMesh, uint32_t& count, float_t*& buffer)
    {
    	static float_t *tempBuffer = nullptr;
    	delete tempBuffer;

    	Vector3 *verts;
    	collMesh -> GetVertexBuffer(count, verts);

    	tempBuffer = new float_t[count * 3];

    	for (int i = 0; i < (int)count; i++)
    	{
    		Vector3& curVec = verts[i];

    		tempBuffer[3*i]     = curVec.m_X; 
    		tempBuffer[3*i + 1] = curVec.m_Y; 
    		tempBuffer[3*i + 2] = curVec.m_Z; 
    	}

    	buffer = tempBuffer;
    }



	const char* ENUM_TopologyToString(ETopology topology)
	{
		static Types::String lastToString;
		lastToString = TopologyToString(topology);
		return lastToString.Buffer();
	}

	const char* ENUM_MaterialFlagsToString(EMaterialFlags flags)
	{
		static Types::String lastToString;
		lastToString = MaterialFlagsToString(flags);
		return lastToString.Buffer();
	}

	const char* ENUM_VBUFFlagsToString(EVBUFFlags flags)
	{
		static Types::String lastToString;
		lastToString = VBUFFlagsToString(flags);
		return lastToString.Buffer();
	}
}