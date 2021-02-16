#include "stdafx.h"
#include "Level.h"
#include "InternalHelpers.h"

#include "Chunks/LVL/LVL.h"

#include "Chunks/LVL/tex_/tex_.h"
#include "Chunks/LVL/modl/LVL.modl.h"
#include "Chunks/LVL/scr_/scr_.h"
#include "Chunks/LVL/Locl/Locl.h"
#include "Chunks/LVL/coll/coll.h"
#include "Chunks/LVL/zaa_/zaa_.h"
#include "Chunks/LVL/tern/tern.h"
#include "Chunks/LVL/config/ConfigChunk.h"

#include <unordered_map>
#include <filesystem>

namespace fs = std::filesystem;

namespace LibSWBF2::Wrappers
{
	using Chunks::GenericBaseChunk;
	using Chunks::LVL::texture::tex_;
	using Chunks::LVL::modl::modl;
	using Chunks::LVL::terrain::tern;
    using namespace Chunks::LVL::common;
    using namespace Chunks::LVL::coll;
    using namespace Chunks::LVL::animation;
    using namespace Chunks::LVL::config;

	Level::Level(LVL* lvl, Container* mainContainer)
	{
		p_lvl = lvl;
		m_NameToIndexMaps = new MapsWrapper();
		p_MainContainer = mainContainer;
	}

	Level::~Level()
	{
		m_Models.Clear();
		m_Textures.Clear();
		m_EntityClasses.Clear();

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
		
		zaa_* animationChunk = dynamic_cast<zaa_*>(root);
		if (animationChunk != nullptr)
		{
			AnimationBank animBank;
			if (AnimationBank::FromChunk(animationChunk, animBank))
			{
				m_NameToIndexMaps->AnimationBankNameToIndex.emplace(ToLower(animBank.GetName()), m_AnimationBanks.Add(std::move(animBank)));
			}	
		}

		//Config chunks
		fx__* fxChunk = dynamic_cast<fx__*>(root);
		if (fxChunk != nullptr)
		{
			Config effect;
			if (Config::FromChunk(fxChunk, effect))
			{
				m_Configs.Add(effect);
			}
		}

		lght* lightListChunk = dynamic_cast<lght*>(root);
		if (lightListChunk != nullptr)
		{
			Config lighting;
			if (Config::FromChunk(lightListChunk, lighting))
			{
				m_Configs.Add(lighting);
			}
		}

		sky_* skydomeChunk = dynamic_cast<sky_*>(root);
		if (skydomeChunk != nullptr)
		{
			Config skydome;
			if (Config::FromChunk(skydomeChunk, skydome))
			{
				m_Configs.Add(skydome);
			}
		}

		path* pathChunk = dynamic_cast<path*>(root);
		if (pathChunk != nullptr)
		{
			Config path;
			if (Config::FromChunk(pathChunk, path))
			{
				m_Configs.Add(path);
			}
		}

		comb* comboChunk = dynamic_cast<comb*>(root);
		if (comboChunk != nullptr)
		{
			Config combo;
			if (Config::FromChunk(comboChunk, combo))
			{
				m_Configs.Add(combo);
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

		coll* collisionChunk = dynamic_cast<coll*>(root);
		if (collisionChunk != nullptr)
		{
			CollisionMesh collMesh;
			if (CollisionMesh::FromChunk(collisionChunk, collMesh))
			{
				if (m_NameToIndexMaps -> ModelNameToIndex.count(ToLower(collMesh.GetName())) == 1)
				{
					size_t modelIndex = m_NameToIndexMaps -> ModelNameToIndex[ToLower(collMesh.GetName())];
					m_Models[modelIndex].m_CollisionMesh = collMesh;
				}
				else 
				{
					LOG_ERROR("CollisionMesh references missing model {}", collMesh.GetName());
				}
			}
		}
		
		prim* primChunk = dynamic_cast<prim*>(root);
		if (primChunk != nullptr)
		{
			List<CollisionPrimitive> primitives;
			auto& NAMEList = primChunk -> m_PrimitiveNAMEs;
			auto& MASKList = primChunk -> m_PrimitiveMASKs;
			auto& PRNTList = primChunk -> m_PrimitivePRNTs;
			auto& XFRMList = primChunk -> m_PrimitiveXFRMs;
			auto& DATAList = primChunk -> m_PrimitiveDATAs;
			
			for (int i = 0; i < primChunk -> p_InfoChunk -> m_NumPrimitives; i++)
			{
				CollisionPrimitive newPrimitive;

				if (CollisionPrimitive::FromChunks(NAMEList[i], MASKList[i], 
												PRNTList[i], XFRMList[i], 
												DATAList[i], newPrimitive))
				{
					primitives.Add(newPrimitive);	
				}
			}

			String& modelName = primChunk -> p_InfoChunk -> m_ModelName;

			if (m_NameToIndexMaps -> ModelNameToIndex.count(
				ToLower(modelName)) == 1)
			{
				size_t modelIndex = m_NameToIndexMaps -> ModelNameToIndex[ToLower(modelName)];
				m_Models[modelIndex].m_CollisionPrimitives = std::move(primitives);	
			} 
			else
			{
				LOG_ERROR("CollisionPrimitive references missing model {}", modelName);
			}
		}

		wrld* worldChunk = dynamic_cast<wrld*>(root);
		if (worldChunk != nullptr)
		{
			// LVLs potentially contain the SAME wrld chunk more than once...
			// Check for wrld name to prevent duplicates!
			std::string name = ToLower(worldChunk->p_Name->m_Text);
			if (m_NameToIndexMaps->WorldNameToIndex.find(name) == m_NameToIndexMaps->WorldNameToIndex.end())
			{
				World world;
				if (World::FromChunk(p_MainContainer, worldChunk, world))
				{
					m_NameToIndexMaps->WorldNameToIndex.emplace(name, m_Worlds.Add(std::move(world)));
				}
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
  
	const List<Localization>& Level::GetLocalizations() const
	{
		return m_Localizations;
	}

	const List<EntityClass>& Level::GetEntityClasses() const
	{
		return m_EntityClasses;
	}

	const List<AnimationBank>& Level::GetAnimationBanks() const
	{
		return m_AnimationBanks;
	}


	const List<const Config *> Level::GetConfigs(EConfigType cfgType) const
	{
		List<const Config *> matchedConfigs;
		for (int i = 0; i < m_Configs.Size(); i++)
		{
			const Config& cfg = m_Configs[i];

			if (cfg.m_ConfigType == cfgType ||
				cfgType == EConfigType::All)
			{
				matchedConfigs.Add(&cfg);
			}
		}

		return matchedConfigs;
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


	const AnimationBank* Level::GetAnimationBank(String setName) const
	{
		if (setName.IsEmpty())
		{
			return nullptr;
		}

		auto it = m_NameToIndexMaps->AnimationBankNameToIndex.find(ToLower(setName));
		if (it != m_NameToIndexMaps->AnimationBankNameToIndex.end())
		{
			return &m_AnimationBanks[it->second];
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


	const Config* Level::GetConfig(EConfigType cfgType, FNVHash hash) const
	{
		for (int i = 0; i < m_Configs.Size(); i++)
		{
			const Config& cfg = m_Configs[i];

			if (cfg.m_Name == hash && cfg.m_ConfigType == cfgType)
			{
				return &cfg;
			}
		}

		return nullptr;
	}
}
