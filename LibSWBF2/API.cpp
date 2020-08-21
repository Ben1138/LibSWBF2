#include "stdafx.h"
#include "API.h"
#include "InternalHelpers.h"
#include "Types/LibString.h"
#include "Chunks/MSH/MSH.h"

#include <iostream>
#define COUT(x) std::cout << x << std::endl

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

	const Model* Level_GetModel(const Level* level, const char* modelName)
	{
		CheckPtr(level, nullptr);
		return level->GetModel(modelName);
	}

	const char* Terrain_GetTexNames(const Terrain *tern)
	{
		CheckPtr(tern, nullptr);
        const List<String>& texNames = tern -> GetLayerTextures();
        String temp = String();
        temp = temp + texNames[0];
        temp = temp + texNames[1];
        String *result = new String(temp);
        return result -> Buffer();
	}

    const void Terrain_GetVerts(const Terrain* ter, uint32_t& numVerts, float_t *& result)
    {
        ter -> GetVertexBufferRaw(numVerts, result);
        COUT("GOT VERTS");

    }

    const void Terrain_GetIndicies(const Terrain* ter, uint32_t& numInds, uint32_t *& result)
    {
        ter -> GetIndexBuffer(ETopology::TriangleList, numInds, result);
    }

	const Terrain* Level_GetTerrain(const Level* level)
	{
		CheckPtr(level, nullptr);
        return &(level -> GetTerrains()[0]);
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
