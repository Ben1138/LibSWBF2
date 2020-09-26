#include "stdafx.h"
#include "Level.h"
#include "InternalHelpers.h"
#include "Chunks/LVL/tex_/tex_.h"
#include "Chunks/LVL/modl/LVL.modl.h"
#include "Chunks/LVL/scr_/scr_.h"
#include "Chunks/LVL/lght/lght.h"
#include "Chunks/LVL/Locl/Locl.h"
#include <unordered_map>
#include <filesystem>

namespace fs = std::filesystem;

namespace LibSWBF2::Wrappers
{
	using Chunks::GenericBaseChunk;
	using Chunks::LVL::texture::tex_;
	using Chunks::LVL::modl::modl;
	using Chunks::LVL::terrain::tern;
	using Chunks::LVL::lght::lght;
    using namespace Chunks::LVL::common;
    using namespace Chunks::LVL::lght;

	Level::Level(LVL* lvl, Container* mainContainer)
	{
		p_lvl = lvl;
		m_NameToIndexMaps = new MapsWrapper();
		m_bHasGlobalLighting = false;
		p_MainContainer = mainContainer;
	}

	Level::~Level()
	{
		m_Models.Clear();
		m_Textures.Clear();
		m_Lights.Clear();

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
				m_NameToIndexMaps->TextureNameToIndex.emplace(ToLower(texture.GetName()), m_Textures.Add(std::move(texture)));
			}
		}

		lght* lightListChunk = dynamic_cast<lght*>(root);
		if (lightListChunk != nullptr)
		{
            for (int i = 0; i < lightListChunk->p_LightTags.Size(); i++)
			{
                Light newLight;
                if (Light::FromChunks(lightListChunk -> p_LightTags[i], 
                					  lightListChunk ->	p_LightBodies[i], 
                					  newLight))
                {
                    m_NameToIndexMaps->LightNameToIndex.emplace(ToLower(newLight.GetName()), m_Lights.Add(newLight));
                }
			}

			if (lightListChunk -> p_GlobalLightingBody)
			{
				if (m_bHasGlobalLighting)
				{
					LOG_WARN("Encountered another Global Lighting setting! Loaded more than one world LVL at once?");
				}

				m_bHasGlobalLighting = GlobalLightingConfig::FromChunk(lightListChunk -> p_GlobalLightingBody, m_GlobalLightingConfig);
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
				m_NameToIndexMaps->ModelNameToIndex.emplace(ToLower(model.GetName()), m_Models.Add(std::move((model))));
			}
		}

		wrld* worldChunk = dynamic_cast<wrld*>(root);
		if (worldChunk != nullptr)
		{
			World world;
			if (World::FromChunk(p_MainContainer, worldChunk, world))
			{
				m_NameToIndexMaps->WorldNameToIndex.emplace(ToLower(world.GetName()), m_Worlds.Add(std::move(world)));
			}
		}

		tern* terrainChunk = dynamic_cast<tern*>(root);
		if (terrainChunk != nullptr)
		{
			Terrain terrain;
			if (Terrain::FromChunk(terrainChunk, terrain))
			{
				m_NameToIndexMaps->TerrainNameToIndex.emplace(ToLower(terrain.GetName()), m_Terrains.Add(std::move(terrain)));
			}
		}

		scr_* scriptChunk = dynamic_cast<scr_*>(root);
		if (scriptChunk != nullptr)
		{
			Script script;
			if (Script::FromChunk(scriptChunk, script))
			{
				m_NameToIndexMaps->ScriptNameToIndex.emplace(ToLower(script.GetName()), m_Scripts.Add(std::move(script)));
			}
		}

		Locl* loclChunk = dynamic_cast<Locl*>(root);
		if (loclChunk != nullptr)
		{
			Localization localization;
			if (Localization::FromChunk(loclChunk, localization))
			{
				m_NameToIndexMaps->LocalizationNameToIndex.emplace(ToLower(localization.GetName()), m_Localizations.Add(std::move(localization)));
			}
		}

		entc* entityChunk = dynamic_cast<entc*>(root);
		if (entityChunk != nullptr)
		{
			EntityClass entityClass;
			if (EntityClass::FromChunk(p_MainContainer, entityChunk, entityClass))
			{
				m_NameToIndexMaps->EntityClassTypeToIndex.emplace(ToLower(entityClass.GetTypeName()), m_EntityClasses.Add(std::move(entityClass)));
			}
		}

		ordc* ordenanceChunk = dynamic_cast<ordc*>(root);
		if (ordenanceChunk != nullptr)
		{
			EntityClass entityClass;
			if (EntityClass::FromChunk(p_MainContainer, ordenanceChunk, entityClass))
			{
				m_NameToIndexMaps->EntityClassTypeToIndex.emplace(ToLower(entityClass.GetTypeName()), m_EntityClasses.Add(std::move(entityClass)));
			}
		}

		wpnc* weaponChunk = dynamic_cast<wpnc*>(root);
		if (weaponChunk != nullptr)
		{
			EntityClass entityClass;
			if (EntityClass::FromChunk(p_MainContainer, weaponChunk, entityClass))
			{
				m_NameToIndexMaps->EntityClassTypeToIndex.emplace(ToLower(entityClass.GetTypeName()), m_EntityClasses.Add(std::move(entityClass)));
			}
		}

		expc* explosionChunk = dynamic_cast<expc*>(root);
		if (explosionChunk != nullptr)
		{
			EntityClass entityClass;
			if (EntityClass::FromChunk(p_MainContainer, explosionChunk, entityClass))
			{
				m_NameToIndexMaps->EntityClassTypeToIndex.emplace(ToLower(entityClass.GetTypeName()), m_EntityClasses.Add(std::move(entityClass)));
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

		Level* result = new Level(lvl, nullptr);
		result->ExploreChildrenRecursive(lvl);
		result->m_FullPath = path;

		return result;
	}

	Level* Level::FromChunk(LVL* lvl, Container* mainContainer)
	{
		if (lvl == nullptr)
		{
			LOG_WARN("Given LVL chunk is NULL!");
			return nullptr;
		}

		Level* result = new Level(lvl, mainContainer);
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

	const String& Level::GetLevelPath() const
	{
		return m_FullPath;
	}

	String Level::GetLevelName() const
	{
		return (const char*)fs::path(m_FullPath.Buffer()).filename().c_str();
	}

	bool Level::IsWorldLevel() const
	{
		return m_Worlds.Size() > 0;
	}

	const List<Light>& Level::GetLights() const
	{
		return m_Lights;
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

	const Light* Level::GetLight(String lightName) const
	{
		if (lightName.IsEmpty())
		{
			return nullptr;
		}

		auto it = m_NameToIndexMaps->LightNameToIndex.find(ToLower(lightName));
		if (it != m_NameToIndexMaps->LightNameToIndex.end())
		{
			return &m_Lights[it->second];
		}

		//LOG_WARN("Could not find Light '{}'!", lightName);
		return nullptr;
	}
  
	const List<Localization>& Level::GetLocalizations() const
	{
		return m_Localizations;
	}

	const GlobalLightingConfig* Level::GetGlobalLighting() const
	{
		if (!m_bHasGlobalLighting)
		{
			return nullptr;
		}
		return &m_GlobalLightingConfig;
	}

	const List<EntityClass>& Level::GetEntityClasses() const
	{
		return m_EntityClasses;
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

		return nullptr;
	}

	const Localization* Level::GetLocalization(String loclName) const
	{
		if (loclName.IsEmpty())
		{
			return nullptr;
		}

		auto it = m_NameToIndexMaps->LocalizationNameToIndex.find(ToLower(loclName));
		if (it != m_NameToIndexMaps->LocalizationNameToIndex.end())
		{
			return &m_Localizations[it->second];
		}

		return nullptr;
	}

	const EntityClass* Level::GetEntityClass(String typeName) const
	{
		if (typeName.IsEmpty())
		{
			return nullptr;
		}

		auto it = m_NameToIndexMaps->EntityClassTypeToIndex.find(ToLower(typeName));
		if (it != m_NameToIndexMaps->EntityClassTypeToIndex.end())
		{
			return &m_EntityClasses[it->second];
		}

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

		return nullptr;
	}
}
