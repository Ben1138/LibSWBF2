#include "pch.h"
#include "World.h"
#include "Instance.h"
#include "Terrain.h"
#include "InternalHelpers.h"
#include "Container.h"

#include "Chunks/LVL/wrld/wrld.h"
#include "Chunks/LVL/wrld/anmg.INFO.h"
#include "Chunks/LVL/wrld/anmh.INFO.h"


namespace LibSWBF2::Wrappers
{

	// HintNode

	bool HintNode::FromChunk(Hint* chunk, HintNode& hintOut)
	{
		if (chunk -> p_Info == nullptr ||
			chunk -> p_Info -> p_Name == nullptr ||
			chunk -> p_Info -> p_Type == nullptr ||
			chunk -> p_Info -> p_Transform == nullptr)
		{
			return false;
		}

		hintOut.p_HintNode = chunk;
		return true;
	}

	const String& HintNode::GetName() const
	{
		return p_HintNode -> p_Info -> p_Name -> m_Text;
	}

	const Vector3& HintNode::GetPosition() const
	{
		return p_HintNode -> p_Info -> p_Transform -> m_Position;
	}

	Vector4 HintNode::GetRotation() const
	{
		return MatrixToQuaternion(p_HintNode -> p_Info -> p_Transform -> m_RotationMatrix);
	}

	const uint16_t& HintNode::GetType() const
	{
		return p_HintNode -> p_Info -> p_Type -> m_Type;
	}




	// Barrier

	bool Barrier::FromChunk(BARR* chunk, Barrier& barrOut)
	{
		if (chunk -> p_Info == nullptr ||
			chunk -> p_Info -> p_Name == nullptr ||
			chunk -> p_Info -> p_Flag == nullptr ||
			chunk -> p_Info -> p_Size == nullptr ||
			chunk -> p_Info -> p_Transform == nullptr)
		{
			return false;
		}

		barrOut.p_Barrier = chunk;
		return true;
	}

	const String& Barrier::GetName() const
	{
		return p_Barrier -> p_Info -> p_Name -> m_Text;
	}

	const Vector3& Barrier::GetPosition() const
	{
		return p_Barrier -> p_Info -> p_Transform -> m_Position;
	}

	Vector4 Barrier::GetRotation() const
	{
		return MatrixToQuaternion(p_Barrier -> p_Info -> p_Transform -> m_RotationMatrix);
	}

	const Vector3& Barrier::GetSize() const
	{
		return p_Barrier -> p_Info -> p_Size -> m_Dimensions;
	}

	const uint32_t& Barrier::GetFlag() const
	{
		return p_Barrier -> p_Info -> p_Flag -> m_Flag;
	}



	// Region

	bool Region::FromChunk(regn* chunk, Region& regOut)
	{
		if (chunk -> p_Info == nullptr ||
			chunk -> p_Info -> p_Name == nullptr ||
			chunk -> p_Info -> p_Type == nullptr ||
			chunk -> p_Info -> p_SIZE == nullptr ||
			chunk -> p_Info -> p_XFRM == nullptr)
		{
			return false;
		}

		regOut.p_Region = chunk;
		return true;
	}

	const String& Region::GetName() const
	{
		return p_Region -> p_Info -> p_Name -> m_Text;
	}

	const Vector3& Region::GetPosition() const
	{
		return p_Region -> p_Info -> p_XFRM -> m_Position;
	}

	Vector4 Region::GetRotation() const
	{
		return MatrixToQuaternion(p_Region -> p_Info -> p_XFRM -> m_RotationMatrix);
	}

	const Vector3& Region::GetSize() const
	{
		return p_Region -> p_Info -> p_SIZE -> m_Dimensions;
	}

	const String& Region::GetType() const
	{
		return p_Region -> p_Info -> p_Type -> m_Text;
	}


	// World Animation

	bool WorldAnimation::FromChunk(anim* chunk, WorldAnimation& animOut)
	{
		if (chunk -> p_Info == nullptr)
		{
			return false;
		}

		animOut.p_WorldAnimation = chunk;
		return true;
	}

	const String& WorldAnimation::GetName() const
	{
		return p_WorldAnimation -> p_Info -> m_Name;
	}

	const float WorldAnimation::GetRunTime() const
	{
		return p_WorldAnimation -> p_Info -> m_RunTime;
	}


	const bool WorldAnimation::IsLooping() const
	{
		return p_WorldAnimation -> p_Info -> m_Looping == 1;
	}

	const bool WorldAnimation::IsTranslationLocal() const
	{
		return p_WorldAnimation -> p_Info -> m_LocalTranslation == 1;
	}

	List<WorldAnimationKey> WorldAnimation::GetRotationKeys() const
	{
		List<WorldAnimationKey> AnimKeys;
		for (int i = 0; i < p_WorldAnimation -> m_RotationKeys.Size(); i++)
		{
			ROTK *currKey = p_WorldAnimation -> m_RotationKeys[i];
			AnimKeys.Add(currKey -> m_Key);
		}	
		return AnimKeys;	
	}
	
	List<WorldAnimationKey> WorldAnimation::GetPositionKeys() const
	{
		List<WorldAnimationKey> AnimKeys;
		for (int i = 0; i < p_WorldAnimation -> m_PositionKeys.Size(); i++)
		{
			POSK *currKey = p_WorldAnimation -> m_PositionKeys[i];
			AnimKeys.Add(currKey -> m_Key);
		}		
		return AnimKeys;
	}



	// World Animation Group

	bool WorldAnimationGroup::FromChunk(anmg* chunk, WorldAnimationGroup& groupOut)
	{
		if (chunk -> p_Info == nullptr)
		{
			return false;
		}

		groupOut.p_WorldAnimationGroup = chunk;
		return true;
	}

	const String& WorldAnimationGroup::GetName() const
	{
		return p_WorldAnimationGroup -> p_Info -> m_Name;	
	}

	const bool WorldAnimationGroup::IsPlayingAtStart() const
	{
		return p_WorldAnimationGroup -> p_Info -> m_PlayAtStart == 1;
	}

	const bool WorldAnimationGroup::IsStoppedOnControl() const
	{
		return p_WorldAnimationGroup -> p_Info -> m_StopOnControl == 1;
	}

	const bool WorldAnimationGroup::DisablesHierarchies() const
	{
		return p_WorldAnimationGroup -> p_NoHierarchy != nullptr;
	}

	const void WorldAnimationGroup::GetAnimationInstancePairs(
									List<String>& animNamesOut, 
									List<String>& instanceNamesOut) const
	{
		animNamesOut.Clear();
		instanceNamesOut.Clear();

		for (uint16_t j = 0; j < p_WorldAnimationGroup -> m_AnimObjectPairs.Size(); j++)
		{
			auto& pair = p_WorldAnimationGroup -> m_AnimObjectPairs[j] -> m_Texts;
			if (pair.Size() != 2)
			{
				continue;
			}

			animNamesOut.Add(pair[0]);
			instanceNamesOut.Add(pair[1]);
		}
	}



	// World Animation Hierarchy

	bool WorldAnimationHierarchy::FromChunk(anmh* chunk, WorldAnimationHierarchy& hierOut)
	{
		if (chunk -> p_Info == nullptr || chunk -> p_Info -> m_NumStrings == 0)
		{
			return false;
		}

		hierOut.p_WorldAnimationHierarchy = chunk;
		return true;
	}

	const String& WorldAnimationHierarchy::GetRootName() const
	{
		return p_WorldAnimationHierarchy -> p_Info -> m_RootName;
	}

	const List<String>& WorldAnimationHierarchy::GetChildNames() const
	{
		return p_WorldAnimationHierarchy -> p_Info -> m_ChildNames;		
	}
	


	// World

	bool World::FromChunk(Container* mainContainer, wrld* worldChunk, World& out)
	{
		if (worldChunk == nullptr)
		{
			LOG_ERROR("Given worldChunk was NULL!");
			return false;
		}

		out.p_World = worldChunk;
		out.m_MainContainer = mainContainer;

		List<inst*>& instances = worldChunk->m_Instances;
		for (size_t i = 0; i < instances.Size(); ++i)
		{
			Instance instance;
			if (Instance::FromChunk(mainContainer, instances[i], instance))
			{
				out.m_Instances.Add(instance);
			}
		}

		List<regn *>& regions = worldChunk -> m_Regions;
		for (size_t i = 0; i < regions.Size(); ++i)
		{
			Region region;
			if (Region::FromChunk(regions[i], region))
			{
				out.m_Regions.Add(region);
			}
		}

		List<BARR *>& barriers = worldChunk -> m_Barriers;
		for (size_t i = 0; i < barriers.Size(); ++i)
		{
			Barrier barrier;
			if (Barrier::FromChunk(barriers[i], barrier))
			{
				out.m_Barriers.Add(barrier);
			}
		}

		List<Hint *>& hintNodes = worldChunk -> m_HintNodes;
		for (size_t i = 0; i < hintNodes.Size(); ++i)
		{
			HintNode hintNode;
			if (HintNode::FromChunk(hintNodes[i], hintNode))
			{
				out.m_HintNodes.Add(hintNode);
			}
		}

		List<anim *>& animations = worldChunk -> m_Animations;
		for (size_t i = 0; i < animations.Size(); ++i)
		{
			WorldAnimation anim;
			if (WorldAnimation::FromChunk(animations[i], anim))
			{
				out.m_Animations.Add(anim);
			}
		}

		List<anmg *>& animationGroups = worldChunk -> m_AnimationGroups;
		for (size_t i = 0; i < animationGroups.Size(); ++i)
		{
			WorldAnimationGroup group;
			if (WorldAnimationGroup::FromChunk(animationGroups[i], group))
			{
				out.m_AnimationGroups.Add(group);
			}
		}		

		List<anmh *>& animationHiers = worldChunk -> m_AnimationHierarchies;
		for (size_t i = 0; i < animationHiers.Size(); ++i)
		{
			WorldAnimationHierarchy hier;
			if (WorldAnimationHierarchy::FromChunk(animationHiers[i], hier))
			{
				out.m_AnimationHierarchies.Add(hier);
			}
		}

		return true;
	}

	const String& World::GetName() const
	{
		return p_World->p_Name->m_Text;
	}

	const List<Instance>& World::GetInstances() const
	{
		return m_Instances;
	}

	const List<Region>& World::GetRegions() const
	{
		return m_Regions;
	}

	const List<Barrier>& World::GetBarriers() const
	{
		return m_Barriers;
	}

	const List<HintNode>& World::GetHintNodes() const
	{
		return m_HintNodes;
	}

	Types::String World::GetTerrainName() const
	{
		return p_World->p_TerrainName != nullptr ? p_World->p_TerrainName->m_Text : "";
	}

	const Terrain* World::GetTerrain() const
	{
		if (m_MainContainer == nullptr || p_World->p_TerrainName == nullptr)
		{
			return nullptr;
		}
		return m_MainContainer->FindTerrain(p_World->p_TerrainName->m_Text);
	}
	
	Types::String World::GetSkyName() const
	{
		return p_World->p_SkyName != nullptr ? p_World->p_SkyName->m_Text : "";
	}
	
	const List<WorldAnimation>& World::GetAnimations() const
	{
		return m_Animations;
	}

	const List<WorldAnimationGroup>& World::GetAnimationGroups() const
	{
		return m_AnimationGroups;
	}

	const List<WorldAnimationHierarchy>& World::GetAnimationHierarchies() const
	{
		return m_AnimationHierarchies;
	}
}