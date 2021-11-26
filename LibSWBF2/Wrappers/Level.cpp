#include "pch.h"
#include "Level.h"

#include "Wrappers/Wrappers.h"

#include "InternalHelpers.h"

#include "Chunks/LVL/LVL.h"

#include "Chunks/LVL/skel/skel.h"
#include "Chunks/LVL/tex_/tex_.h"
#include "Chunks/LVL/modl/LVL.modl.h"
#include "Chunks/LVL/scr_/scr_.h"
#include "Chunks/LVL/Locl/Locl.h"
#include "Chunks/LVL/coll/coll.h"
#include "Chunks/LVL/zaa_/zaa_.h"
#include "Chunks/LVL/zaf_/zaf_.h"
#include "Chunks/LVL/tern/tern.h"
#include "Chunks/LVL/config/ConfigChunk.h"
#include "Chunks/LVL/common/GenericClass.h"
#include "Chunks/LVL/wrld/wrld.h"
#include "Chunks/LVL/sound/Stream.h"
#include "Chunks/LVL/sound/SampleBank.h"
#include "Chunks/LVL/sound/SampleBankInfo.h"


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
    using namespace Chunks::LVL::sound;

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
				m_NameToIndexMaps->TextureNameToIndex.emplace(FNV::Hash(texture.GetName()), m_Textures.Add(std::move(texture)));
			}
		}
		
		zaa_* animationChunk = dynamic_cast<zaa_*>(root);
		if (animationChunk != nullptr)
		{
			AnimationBank animBank;
			if (AnimationBank::FromChunk(animationChunk, animBank))
			{
				m_NameToIndexMaps->AnimationBankNameToIndex.emplace(FNV::Hash(animBank.GetName()), m_AnimationBanks.Add(animBank));
			}	
		}

		zaf_* animSkelChunk = dynamic_cast<zaf_*>(root);
		if (animSkelChunk != nullptr)
		{
			AnimationSkeleton animSkel;
			if (AnimationSkeleton::FromChunk(animSkelChunk, animSkel))
			{
				m_NameToIndexMaps->AnimationSkeletonNameToIndex.emplace(FNV::Hash(animSkel.GetName()), m_AnimationSkeletons.Add(animSkel));
			}	
		}

		//Config chunks
		fx__* fxChunk = dynamic_cast<fx__*>(root);
		if (fxChunk != nullptr)
		{
			Config effect;
			if (Config::FromChunk(fxChunk, effect))
			{
				m_NameToIndexMaps->ConfigHashToIndex.emplace(effect.m_Name + (uint32_t) effect.m_Type, m_Configs.Add(std::move(effect)));
			}
		}

		lght* lightListChunk = dynamic_cast<lght*>(root);
		if (lightListChunk != nullptr)
		{
			Config lighting;
			if (Config::FromChunk(lightListChunk, lighting))
			{
				m_NameToIndexMaps->ConfigHashToIndex.emplace(lighting.m_Name + (uint32_t) lighting.m_Type, m_Configs.Add(std::move(lighting)));
			}
		}

		sky_* skydomeChunk = dynamic_cast<sky_*>(root);
		if (skydomeChunk != nullptr)
		{
			Config skydome;
			if (Config::FromChunk(skydomeChunk, skydome))
			{
				m_NameToIndexMaps->ConfigHashToIndex.emplace(skydome.m_Name + (uint32_t) skydome.m_Type, m_Configs.Add(std::move(skydome)));
			}
		}

		path* pathChunk = dynamic_cast<path*>(root);
		if (pathChunk != nullptr)
		{
			Config path;
			if (Config::FromChunk(pathChunk, path))
			{
				m_NameToIndexMaps->ConfigHashToIndex.emplace(path.m_Name + (uint32_t) path.m_Type, m_Configs.Add(std::move(path)));
			}
		}

		comb* comboChunk = dynamic_cast<comb*>(root);
		if (comboChunk != nullptr)
		{
			Config combo;
			if (Config::FromChunk(comboChunk, combo))
			{
				m_NameToIndexMaps->ConfigHashToIndex.emplace(combo.m_Name + (uint32_t) combo.m_Type, m_Configs.Add(std::move(combo)));
			}
		}

		snd_* soundChunk = dynamic_cast<snd_*>(root);
		if (soundChunk != nullptr)
		{
			Config sound;
			if (Config::FromChunk(soundChunk, sound))
			{
				m_NameToIndexMaps->ConfigHashToIndex.emplace(sound.m_Name + (uint32_t) sound.m_Type, m_Configs.Add(std::move(sound)));
			}
		}

		mus_* musicChunk = dynamic_cast<mus_*>(root);
		if (musicChunk != nullptr)
		{
			Config music;
			if (Config::FromChunk(musicChunk, music))
			{
				m_NameToIndexMaps->ConfigHashToIndex.emplace(music.m_Name + (uint32_t) music.m_Type, m_Configs.Add(std::move(music)));
			}
		}

		ffx_* foleyFXChunk = dynamic_cast<ffx_*>(root);
		if (foleyFXChunk != nullptr)
		{
			Config foleyFX;
			if (Config::FromChunk(foleyFXChunk, foleyFX))
			{
				m_NameToIndexMaps->ConfigHashToIndex.emplace(foleyFX.m_Name + (uint32_t) foleyFX.m_Type, m_Configs.Add(std::move(foleyFX)));
			}
		}
		
		tsr_* soundTriggerChunk = dynamic_cast<tsr_*>(root);
		if (soundTriggerChunk != nullptr)
		{
			Config soundTrigger;
			if (Config::FromChunk(soundTriggerChunk, soundTrigger))
			{
				m_NameToIndexMaps->ConfigHashToIndex.emplace(soundTrigger.m_Name + (uint32_t) soundTrigger.m_Type, m_Configs.Add(std::move(soundTrigger)));
			}
		}

		// IMPORTANT: crawl skeletons BEFORE models, so skeleton references via string can be resolved in models
		skel* skelChunk = dynamic_cast<skel*>(root);
		if (skelChunk != nullptr)
		{
			m_NameToIndexMaps->SkeletonNameToSkel.emplace(FNV::Hash(skelChunk->p_Info->m_ModelName), skelChunk);
		}

		// IMPORTANT: crawl models BEFORE worlds, so model references via string can be resolved in worlds
		modl* modelChunk = dynamic_cast<modl*>(root);
		if (modelChunk != nullptr)
		{
			Model model;
			if (Model::FromChunk(this, modelChunk, model))
			{
				m_NameToIndexMaps->ModelNameToIndex.emplace(FNV::Hash(model.GetName()), m_Models.Add(std::move((model))));
			}
		}

		coll* collisionChunk = dynamic_cast<coll*>(root);
		if (collisionChunk != nullptr)
		{
			CollisionMesh collMesh;
			if (CollisionMesh::FromChunk(collisionChunk, collMesh))
			{
				if (m_NameToIndexMaps -> ModelNameToIndex.count(FNV::Hash(collMesh.GetName())) == 1)
				{
					size_t modelIndex = m_NameToIndexMaps -> ModelNameToIndex[FNV::Hash(collMesh.GetName())];
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
				FNV::Hash(modelName)) == 1)
			{
				size_t modelIndex = m_NameToIndexMaps -> ModelNameToIndex[FNV::Hash(modelName)];
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
			FNVHash name = FNV::Hash(worldChunk->p_Name->m_Text);
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
				m_NameToIndexMaps->TerrainNameToIndex.emplace(FNV::Hash(terrain.GetName()), m_Terrains.Add(std::move(terrain)));
			}
		}

		scr_* scriptChunk = dynamic_cast<scr_*>(root);
		if (scriptChunk != nullptr)
		{
			Script script;
			if (Script::FromChunk(scriptChunk, script))
			{
				m_NameToIndexMaps->ScriptNameToIndex.emplace(FNV::Hash(script.GetName()), m_Scripts.Add(std::move(script)));
			}
		}

		Locl* loclChunk = dynamic_cast<Locl*>(root);
		if (loclChunk != nullptr)
		{
			Localization localization;
			if (Localization::FromChunk(loclChunk, localization))
			{
				m_NameToIndexMaps->LocalizationNameToIndex.emplace(FNV::Hash(localization.GetName()), m_Localizations.Add(std::move(localization)));
			}
		}

		entc* entityChunk = dynamic_cast<entc*>(root);
		if (entityChunk != nullptr)
		{
			EntityClass entityClass;
			if (EntityClass::FromChunk(p_MainContainer, entityChunk, entityClass))
			{
				FNVHash name = FNV::Hash(entityClass.GetTypeName());
				m_NameToIndexMaps->EntityClassTypeToIndex.emplace(name, m_EntityClasses.Add(std::move(entityClass)));
			}
		}

		ordc* ordenanceChunk = dynamic_cast<ordc*>(root);
		if (ordenanceChunk != nullptr)
		{
			EntityClass entityClass;
			if (EntityClass::FromChunk(p_MainContainer, ordenanceChunk, entityClass))
			{
				FNVHash name = FNV::Hash(entityClass.GetTypeName());
				m_NameToIndexMaps->EntityClassTypeToIndex.emplace(name, m_EntityClasses.Add(std::move(entityClass)));
			}
		}

		wpnc* weaponChunk = dynamic_cast<wpnc*>(root);
		if (weaponChunk != nullptr)
		{
			EntityClass entityClass;
			if (EntityClass::FromChunk(p_MainContainer, weaponChunk, entityClass))
			{
				FNVHash name = FNV::Hash(entityClass.GetTypeName());
				m_NameToIndexMaps->EntityClassTypeToIndex.emplace(name, m_EntityClasses.Add(std::move(entityClass)));
			}
		}

		expc* explosionChunk = dynamic_cast<expc*>(root);
		if (explosionChunk != nullptr)
		{
			EntityClass entityClass;
			if (EntityClass::FromChunk(p_MainContainer, explosionChunk, entityClass))
			{
				FNVHash name = FNV::Hash(entityClass.GetTypeName());
				m_NameToIndexMaps->EntityClassTypeToIndex.emplace(name, m_EntityClasses.Add(std::move(entityClass)));
			}
		}

		
		SampleBank* bankChunk = dynamic_cast<SampleBank*>(root);
		if (bankChunk != nullptr)
		{
			SoundBank bank;
			if (SoundBank::FromChunk(bankChunk, bank))
			{
				m_NameToIndexMaps->SoundBankHashToIndex.emplace(bank.GetHashedName(), m_SoundBanks.Add(std::move(bank)));
				
				if (bank.HasData())
				{
					const List<Sound>& sounds = bank.GetSounds(); 
					for (uint32_t i = 0; i < sounds.Size(); i++)
					{
						m_NameToIndexMaps->SoundHashToIndex.emplace(sounds[i].GetHashedName(), m_Sounds.Add(sounds[i]));
					}
				}
			}
		}
		
		Stream* streamChunk = dynamic_cast<Stream*>(root);
		if (streamChunk != nullptr)
		{
			SoundStream stream;
			if (SoundStream::FromChunk(streamChunk, stream))
			{
				m_NameToIndexMaps->SoundStreamHashToIndex.emplace(stream.GetHashedName(), m_SoundStreams.Add(std::move(stream)));
			}
		}


		const List<GenericBaseChunk*>& children = root->GetChildren();
		for (size_t i = 0; i < children.Size(); ++i)
		{
			ExploreChildrenRecursive(children[i]);
		}
	}

	Level* Level::FromFile(const String& path, const List<String>* subLVLsToLoad)
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

	const List<AnimationSkeleton>& Level::GetAnimationSkeletons() const
	{
		return m_AnimationSkeletons;
	}

	const List<Sound>& Level::GetSounds() const
	{
		return m_Sounds;
	}

	const List<const Config *> Level::GetConfigs(EConfigType cfgType) const
	{
		List<const Config *> matchedConfigs;
		for (int i = 0; i < m_Configs.Size(); i++)
		{
			const Config& cfg = m_Configs[i];

			if (cfg.m_Type == cfgType ||
				cfgType == EConfigType::All)
			{
				matchedConfigs.Add(&cfg);
			}
		}

		return matchedConfigs;
	}

	const List<SoundStream>& Level::GetSoundStreams() const
	{
		return m_SoundStreams;
	}

	const List<SoundBank>& Level::GetSoundBanks() const
	{
		return m_SoundBanks;
	}


	// Model
	const Model* Level::GetModel(const String& modelName) const
	{
		return modelName.IsEmpty() ? nullptr : GetModel(FNV::Hash(modelName));
	}

	const Model* Level::GetModel(FNVHash modelName) const
	{
		auto it = m_NameToIndexMaps->ModelNameToIndex.find(modelName);
		if (it != m_NameToIndexMaps->ModelNameToIndex.end())
		{
			return &m_Models[it->second];
		}

		return nullptr;
	}



	// Texture
	const Texture* Level::GetTexture(const String& textureName) const
	{
		return textureName.IsEmpty() ? nullptr : GetTexture(FNV::Hash(textureName));
	}

	const Texture* Level::GetTexture(FNVHash textureName) const
	{
		auto it = m_NameToIndexMaps->TextureNameToIndex.find(textureName);
		if (it != m_NameToIndexMaps->TextureNameToIndex.end())
		{
			return &m_Textures[it->second];
		}

		return nullptr;
	}



	// World
	const World* Level::GetWorld(const String& worldName) const
	{
		return worldName.IsEmpty() ? nullptr : GetWorld(FNV::Hash(worldName));
	}

	const World* Level::GetWorld(FNVHash worldName) const
	{
		auto it = m_NameToIndexMaps->WorldNameToIndex.find(worldName);
		if (it != m_NameToIndexMaps->WorldNameToIndex.end())
		{
			return &m_Worlds[it->second];
		}

		return nullptr;
	}



	// Terrain
	const Terrain* Level::GetTerrain(const String& terrainName) const
	{
		return terrainName.IsEmpty() ? nullptr : GetTerrain(FNV::Hash(terrainName));
	}

	const Terrain* Level::GetTerrain(FNVHash terrainName) const
	{
		auto it = m_NameToIndexMaps->TerrainNameToIndex.find(terrainName);
		if (it != m_NameToIndexMaps->TerrainNameToIndex.end())
		{
			return &m_Terrains[it->second];
		}

		return nullptr;
	}



	// Script
	const Script* Level::GetScript(const String& scriptName) const
	{
		return scriptName.IsEmpty() ? nullptr : GetScript(FNV::Hash(scriptName));
	}

	const Script* Level::GetScript(FNVHash scriptName) const
	{
		auto it = m_NameToIndexMaps->ScriptNameToIndex.find(scriptName);
		if (it != m_NameToIndexMaps->ScriptNameToIndex.end())
		{
			return &m_Scripts[it->second];
		}

		return nullptr;
	}



	// Localization
	const Localization* Level::GetLocalization(const String& locName) const
	{
		return locName.IsEmpty() ? nullptr : GetLocalization(FNV::Hash(locName));
	}

	const Localization* Level::GetLocalization(FNVHash loclName) const
	{
		auto it = m_NameToIndexMaps->LocalizationNameToIndex.find(loclName);
		if (it != m_NameToIndexMaps->LocalizationNameToIndex.end())
		{
			return &m_Localizations[it->second];
		}

		return nullptr;
	}



	// EntityClass
	const EntityClass* Level::GetEntityClass(const String& ecName) const
	{
		return ecName.IsEmpty() ? nullptr : GetEntityClass(FNV::Hash(ecName));
	}

	const EntityClass* Level::GetEntityClass(FNVHash typeName) const
	{
		auto it = m_NameToIndexMaps->EntityClassTypeToIndex.find(typeName);
		if (it != m_NameToIndexMaps->EntityClassTypeToIndex.end())
		{
			return &m_EntityClasses[it->second];
		}

		return nullptr;
	}



	// AnimationBank
	const AnimationBank* Level::GetAnimationBank(const String& bankName) const
	{
		return bankName.IsEmpty() ? nullptr : GetAnimationBank(FNV::Hash(bankName));
	}

	const AnimationBank* Level::GetAnimationBank(FNVHash setName) const
	{
		auto it = m_NameToIndexMaps->AnimationBankNameToIndex.find(setName);
		if (it != m_NameToIndexMaps->AnimationBankNameToIndex.end())
		{
			return &m_AnimationBanks[it->second];
		}

		return nullptr;
	}



	// AnimationSkeleton
	const AnimationSkeleton* Level::GetAnimationSkeleton(const String& skelName) const
	{
		return skelName.IsEmpty() ? nullptr : GetAnimationSkeleton(FNV::Hash(skelName));
	}

	const AnimationSkeleton* Level::GetAnimationSkeleton(FNVHash skelName) const
	{
		auto it = m_NameToIndexMaps->AnimationSkeletonNameToIndex.find(skelName);
		if (it != m_NameToIndexMaps->AnimationSkeletonNameToIndex.end())
		{
			return &m_AnimationSkeletons[it->second];
		}

		return nullptr;
	}



	// Sound
	const Sound* Level::GetSound(const String& soundName) const
	{
		return soundName.IsEmpty() ? nullptr : GetSound(FNV::Hash(soundName));
	}

	const Sound* Level::GetSound(FNVHash soundHashName) const
	{
		auto it = m_NameToIndexMaps->SoundHashToIndex.find(soundHashName);
		if (it != m_NameToIndexMaps->SoundHashToIndex.end())
		{
			return &m_Sounds[it->second];
		}
		return nullptr;
	}



	// Skeleton
	skel* Level::FindSkeleton(const String& skelName) const
	{
		return skelName.IsEmpty() ? nullptr : FindSkeleton(FNV::Hash(skelName));
	}

	skel* Level::FindSkeleton(FNVHash skeletonName) const
	{
		auto it = m_NameToIndexMaps->SkeletonNameToSkel.find(skeletonName);
		if (it != m_NameToIndexMaps->SkeletonNameToSkel.end())
		{
			return it->second;
		}

		return nullptr;
	}



	// Config
	const Config* Level::GetConfig(EConfigType cfgType, const String& cfgName) const
	{
		return cfgName.IsEmpty() ? nullptr : GetConfig(cfgType, FNV::Hash(cfgName));
	}

	const Config* Level::GetConfig(EConfigType cfgType, FNVHash hash) const
	{
		auto it = m_NameToIndexMaps->ConfigHashToIndex.find(hash + (uint32_t) cfgType);
		if (it != m_NameToIndexMaps->ConfigHashToIndex.end())
		{
			return &m_Configs[it->second];
		}

		return nullptr;
	}



	// SoundStream
	const SoundStream* Level::GetSoundStream(const String& streamName) const
	{
		return streamName.IsEmpty() ? nullptr : GetSoundStream(FNV::Hash(streamName));
	}

	const SoundStream* Level::GetSoundStream(FNVHash streamHashName) const
	{
		auto it = m_NameToIndexMaps->SoundStreamHashToIndex.find(streamHashName);
		if (it != m_NameToIndexMaps->SoundStreamHashToIndex.end())
		{
			return &m_SoundStreams[it->second];
		}
		return nullptr;
	}



	// SoundBank
	const SoundBank* Level::GetSoundBank(const String& bankName) const
	{
		return bankName.IsEmpty() ? nullptr : GetSoundBank(FNV::Hash(bankName));
	}

	const SoundBank* Level::GetSoundBank(FNVHash bankHashName) const
	{
		auto it = m_NameToIndexMaps->SoundBankHashToIndex.find(bankHashName);
		if (it != m_NameToIndexMaps->SoundBankHashToIndex.end())
		{
			return &m_SoundBanks[it->second];
		}
		return nullptr;
	}

	const LibSWBF2::Chunks::LVL::LVL* Level::GetChunk() const
	{
		return p_lvl;
	}
}
