#include "stdafx.h"
#include "Level.h"
#include "InternalHelpers.h"
#include "Chunks/LVL/tex_/tex_.h"
#include "Chunks/LVL/modl/LVL.modl.h"
#include "Chunks/LVL/scr_/scr_.h"

#include <unordered_map>

namespace LibSWBF2::Wrappers
{
	class MapsWrapper
	{
	public:
		std::unordered_map<std::string, size_t> TextureNameToIndex;
		std::unordered_map<std::string, size_t> ModelNameToIndex;
		std::unordered_map<std::string, size_t> WorldNameToIndex;
		std::unordered_map<std::string, size_t> TerrainNameToIndex;
		std::unordered_map<std::string, size_t> ScriptNameToIndex;
		std::unordered_map<std::string, skel*> SkeletonNameToSkel;
		std::unordered_map<std::string, size_t> LightNameToIndex;
	};

	using Chunks::GenericBaseChunk;
	using Chunks::LVL::texture::tex_;
	using Chunks::LVL::modl::modl;
	using Chunks::LVL::terrain::tern;

	Level::Level(LVL* lvl)
	{
		p_lvl = lvl;
		m_NameToIndexMaps = new MapsWrapper();
	}

	Level::~Level()
	{
		m_Models.Clear();
		m_Textures.Clear();

		if (p_lvl == nullptr)
		{
			LOG_ERROR("p_lvl of Level was NULL!");
		}
		else
		{
			LVL::Destroy(p_lvl);
		}
		delete m_NameToIndexMaps;
	}

	void Level::ExploreChildrenRecursive(GenericBaseChunk* root)
	{
		// IMPORTANT: crawl textures BEFORE models, so texture references via string can be resolved in models
		tex_* textureChunk = dynamic_cast<tex_*>(root);
		if (textureChunk != nullptr)
		{
			Texture texture;
			if (Texture::FromChunk(textureChunk, texture))
			{
				m_NameToIndexMaps->TextureNameToIndex.emplace(ToLower(texture.GetName()), m_Textures.Add(texture));
			}
		}

		// IMPORTANT: crawl skeletons BEFORE models, so skeleton references via string can be resolved in models
		skel* skelChunk = dynamic_cast<skel*>(root);
		if (skelChunk != nullptr)
		{
			m_NameToIndexMaps->SkeletonNameToSkel.emplace(ToLower(skelChunk->p_Info->m_ModelName), skelChunk);
		}

		// IMPORTANT: crawl models BEFORE worlds, so model references via string can be resolved in worlds
		modl* modelChunk = dynamic_cast<modl*>(root);
		if (modelChunk != nullptr)
		{
			Model model;
			if (Model::FromChunk(this, modelChunk, model))
			{
				m_NameToIndexMaps->ModelNameToIndex.emplace(ToLower(model.GetName()), m_Models.Add(model));
			}
		}

		wrld* worldChunk = dynamic_cast<wrld*>(root);
		if (worldChunk != nullptr)
		{
			World world;
			if (World::FromChunk(this, worldChunk, world))
			{
				m_NameToIndexMaps->WorldNameToIndex.emplace(ToLower(world.GetName()), m_Worlds.Add(world));
			}
		}

		tern* terrainChunk = dynamic_cast<tern*>(root);
		if (terrainChunk != nullptr)
		{
			Terrain terrain;
			if (Terrain::FromChunk(this, terrainChunk, terrain))
			{
				m_NameToIndexMaps->TerrainNameToIndex.emplace(ToLower(terrain.GetName()), m_Terrains.Add(terrain));
			}
		}

		scr_* scriptChunk = dynamic_cast<scr_*>(root);
		if (scriptChunk != nullptr)
		{
			Script script;
			if (Script::FromChunk(scriptChunk, script))
			{
				m_NameToIndexMaps->ScriptNameToIndex.emplace(ToLower(script.GetName()), m_Scripts.Add(script));
			}
		}

		const List<GenericBaseChunk*>& children = root->GetChildren();
		for (size_t i = 0; i < children.Size(); ++i)
		{
			ExploreChildrenRecursive(children[i]);
		}
	}

	Level* Level::FromFile(String path, const List<String>* subLVLsToLoad)
	{
		LVL* lvl = LVL::Create();
		if (!lvl->ReadFromFile(path, subLVLsToLoad))
		{
			LVL::Destroy(lvl);
			return nullptr;
		}
		
		Level* result = new Level(lvl);
		result->ExploreChildrenRecursive(lvl);

		return result;
	}

	void Level::Destroy(Level* level)
	{
		if (level == nullptr)
		{
			LOG_ERROR("Given level was NULL!");
			return;
		}

		delete level;
	}

	bool Level::IsWorldLevel() const
	{
		return m_Worlds.Size() > 0;
	}

	const List<Model>& Level::GetModels() const
	{
		return m_Models;
	}

	const List<Texture>& Level::GetTextures() const
	{
		return m_Textures;
	}

	const List<World>& Level::GetWorlds() const
	{
		return m_Worlds;
	}

	const List<Terrain>& Level::GetTerrains() const
	{
		return m_Terrains;
	}

	const List<Script>& Level::GetScripts() const
	{
		return m_Scripts;
	}

	const Model* Level::GetModel(String modelName) const
	{
		if (modelName.IsEmpty())
		{
			return nullptr;
		}

		auto it = m_NameToIndexMaps->ModelNameToIndex.find(ToLower(modelName));
		if (it != m_NameToIndexMaps->ModelNameToIndex.end())
		{
			return &m_Models[it->second];
		}

		//LOG_WARN("Could not find Model '{}'!", modelName);
		return nullptr;
	}

	const Texture* Level::GetTexture(String textureName) const
	{
		if (textureName.IsEmpty())
		{
			return nullptr;
		}

		auto it = m_NameToIndexMaps->TextureNameToIndex.find(ToLower(textureName));
		if (it != m_NameToIndexMaps->TextureNameToIndex.end())
		{
			return &m_Textures[it->second];
		}

		//LOG_WARN("Could not find Texture '{}'!", textureName);
		return nullptr;
	}

	const World* Level::GetWorld(String worldName) const
	{
		if (worldName.IsEmpty())
		{
			return nullptr;
		}

		auto it = m_NameToIndexMaps->WorldNameToIndex.find(ToLower(worldName));
		if (it != m_NameToIndexMaps->WorldNameToIndex.end())
		{
			return &m_Worlds[it->second];
		}

		//LOG_WARN("Could not find World '{}'!", worldName);
		return nullptr;
	}

	const Terrain* Level::GetTerrain(String terrainName) const
	{
		if (terrainName.IsEmpty())
		{
			return nullptr;
		}

		auto it = m_NameToIndexMaps->TerrainNameToIndex.find(ToLower(terrainName));
		if (it != m_NameToIndexMaps->TerrainNameToIndex.end())
		{
			return &m_Terrains[it->second];
		}

		//LOG_WARN("Could not find Terrain '{}'!", terrainName);
		return nullptr;
	}

	const Script* Level::GetScript(String scriptName) const
	{
		if (scriptName.IsEmpty())
		{
			return nullptr;
		}

		auto it = m_NameToIndexMaps->ScriptNameToIndex.find(ToLower(scriptName));
		if (it != m_NameToIndexMaps->ScriptNameToIndex.end())
		{
			return &m_Scripts[it->second];
		}

		//LOG_WARN("Could not find Script '{}'!", scriptName);
		return nullptr;
	}

	skel* Level::FindSkeleton(String skeletonName) const
	{
		if (skeletonName.IsEmpty())
		{
			return nullptr;
		}

		auto it = m_NameToIndexMaps->SkeletonNameToSkel.find(ToLower(skeletonName));
		if (it != m_NameToIndexMaps->SkeletonNameToSkel.end())
		{
			return it->second;
		}

		//LOG_WARN("Could not find Skeleton '{}'!", scriptName);
		return nullptr;
	}
}