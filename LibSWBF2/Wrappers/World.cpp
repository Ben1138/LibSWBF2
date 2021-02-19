#include "stdafx.h"
#include "World.h"
#include "Instance.h"
#include "Terrain.h"
#include "InternalHelpers.h"
#include "Container.h"

#include "Chunks/LVL/wrld/wrld.h"


namespace LibSWBF2::Wrappers
{
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


	const List<String> World::GetAnimationNames() const
	{
		List<String> names;
		const List<anim*>& animPtrs = p_World -> m_Animations;
		for (uint16_t i = 0; i < animPtrs.Size(); i++)
		{
			names.Add(animPtrs[i] -> p_Info -> m_Text);
		}
		return names;
	}


	const List<String> World::GetAnimationGroups() const
	{
		List<String> names;
		const List<anmg*>& animGPtrs = p_World -> m_AnimationGroups;
		for (uint16_t i = 0; i < animGPtrs.Size(); i++)
		{
			names.Add(animGPtrs[i] -> p_Info -> m_Text);
		}
		return names;	
	}


	const bool World::GetAnimationGroupPairs(const String& animGroupName, 
									List<String>& animNamesOut, 
									List<String>& instanceNamesOut) const
	{
		animNamesOut.Clear();
		instanceNamesOut.Clear();

		const List<anmg*>& animGPtrs = p_World -> m_AnimationGroups;
		for (uint16_t i = 0; i < animGPtrs.Size(); i++)
		{
			if (animGroupName == animGPtrs[i] -> p_Info -> m_Text)
			{
				for (uint16_t j = 0; j < animGPtrs[i] -> m_AnimObjectPairs.Size(); j++)
				{
					auto& pair = animGPtrs[i] -> m_AnimObjectPairs[i] -> m_Texts;
					if (pair.Size() != 2)
					{
						continue;
					}

					animNamesOut.Add(pair[0]);
					instanceNamesOut.Add(pair[1]);
				}

				return true;
			}
		}

		return false;
	}


	//const Curve<float_t> World::GetAnimationCurve(const String& animName, ECurveType cc) const
	//{
	//	return Curve<float_t>();
	//}
}