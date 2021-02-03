#pragma once
#include "req.h"
#include "Model.h"
#include "Texture.h"
#include "World.h"
#include "Terrain.h"
#include "Script.h"
//#include "Light.h"
#include "Config.h"
#include "AnimationBank.h"
//#include "GlobalLighting.h"
#include "Localization.h"
#include "EntityClass.h"
#include "Types/LibString.h"
#include "Types/List.h"
#include "Chunks/LVL/LVL.h"
#include "CollisionMesh.h"


namespace LibSWBF2
{
	class Container;
}


namespace LibSWBF2::Wrappers
{
	using Types::List;
	using Chunks::GenericBaseChunk;
	using Chunks::LVL::LVL;

	/*
	 * This and the other wrapper classes just serve as abstraction Layers
	 * to wrap around the chunk data. You can of course just use the chunk data
	 * directly if you want. This is just to make access to desired data more
	 * straight forward.
	 */
	class LIBSWBF2_API Level
	{
	private:
		friend Container;

		Level(LVL* lvl, Container* mainContainer);
		~Level();

	private:
		LVL* p_lvl;
		Container* p_MainContainer;	// can be NULL
		String m_FullPath;

		List<Model> m_Models;
		List<Texture> m_Textures;
		List<World> m_Worlds;
		List<Terrain> m_Terrains;	// multiple terrains are possible, in theory. never saw it though
		List<Script> m_Scripts;
		//List<Light> m_Lights;
		List<Localization> m_Localizations;
		List<EntityClass> m_EntityClasses;
		List<AnimationBank> m_AnimationBanks;
		List<Config> m_Configs;



		bool m_bHasGlobalLighting;
		//GlobalLightingConfig m_GlobalLightingConfig;

		// fast pimpl to avoid inclusion of std::unordered_map
		class MapsWrapper* m_NameToIndexMaps;

	public:
		friend class Model;
		friend class Segment;

		void testCall();

		// subLVLsToLoad doesn't need to be persistent, can be a stack value.
		// contents will be copied and hashed.
		static Level* FromFile(String path, const List<String>* subLVLsToLoad = nullptr);
		static Level* FromChunk(LVL* lvl, Container* mainContainer);
		static void Destroy(Level* level);

		const String& GetLevelPath() const;
		String GetLevelName() const;
		bool IsWorldLevel() const;

		//const List<Light>& GetLights() const;
		const List<Model>& GetModels() const;
		const List<Texture>& GetTextures() const;
		const List<World>& GetWorlds() const;
		const List<Terrain>& GetTerrains() const;
		const List<Script>& GetScripts() const;
		const List<Localization>& GetLocalizations() const;
		const List<EntityClass>& GetEntityClasses() const;
		const List<AnimationBank>& GetAnimationBanks() const;


		template<uint32_t Header = 0>
		List<Config *> GetConfigs() const
		{
			List<Config *> matchedConfigs;
			for (int i = 0; i < m_Configs.Size(); i++)
			{
				const Config& cfg = m_Configs[i];

				if (cfg.WrapsConfigType<Header>())
				{
					matchedConfigs.Add(const_cast<Config *>(&cfg));
				}
			}

			return matchedConfigs;
		}

		//const Light* GetLight(String lightName) const;
		//const GlobalLightingConfig* GetGlobalLighting() const;
		const Model* GetModel(String modelName) const;
		const Texture* GetTexture(String textureName) const;
		const World* GetWorld(String worldName) const;
		const Terrain* GetTerrain(String terrainName) const;
		const Script* GetScript(String scriptName) const;
		const Localization* GetLocalization(String loclName) const;
		const EntityClass* GetEntityClass(String typeName) const;
		const AnimationBank* GetAnimationBank(String setName) const; 


		template<uint32_t Header = 0>
		const Config* GetConfig(FNVHash hash) const
		{
			for (int i = 0; i < m_Configs.Size(); i++)
			{
				const Config& cfg = m_Configs[i];

				if (cfg.m_Name == hash && cfg.WrapsConfigType<Header>())
				{
					return &cfg;
				}
			}

			return nullptr;
		}


	private:
		void ExploreChildrenRecursive(GenericBaseChunk* root);
		skel* FindSkeleton(String skeletonName) const;
	};
}
