#include "stdafx.h"
#include "World.h"
#include "InternalHelpers.h"

namespace LibSWBF2::Wrappers
{
	bool World::FromChunk(Level* mainContainer, wrld* worldChunk, World& out)
	{
		if (mainContainer == nullptr)
		{
			LOG_ERROR("Given mainContainer was NULL!");
			return false;
		}
		if (worldChunk == nullptr)
		{
			LOG_ERROR("Given worldChunk was NULL!");
			return false;
		}

		out.p_World = worldChunk;

		List<inst*>& instances = worldChunk->m_Instances;
		for (size_t i = 0; i < instances.Size(); ++i)
		{
			Instance instance;
			if (Instance::FromChunk(mainContainer, instances[i], instance))
			{
				out.m_Instances.Add(instance);
			}
		}
		return true;
	}

	Types::String World::GetName() const
	{
		return p_World->p_Name->m_Text;
	}

	const List<Instance>& World::GetInstances() const
	{
		return m_Instances;
	}

	Types::String World::GetTerrainName() const
	{
		return p_World->p_TerrainName != nullptr ? p_World->p_TerrainName->m_Text : "";
	}
	
	Types::String World::GetSkyName() const
	{
		return p_World->p_SkyName != nullptr ? p_World->p_SkyName->m_Text : "";
	}
}