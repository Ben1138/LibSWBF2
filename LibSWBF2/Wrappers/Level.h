#pragma once
#include "req.h"
#include "API.h"

#include "Types/LibString.h"
#include "Types/List.h"


namespace LibSWBF2
{
	namespace Chunks {
		struct GenericBaseChunk;

		namespace LVL
		{
			struct LVL;
			namespace skel 
			{
				struct skel;
			}
		}
	}

	class Container;
}


namespace LibSWBF2::Wrappers
{
	using Types::List;

	/*
	 * This and the other wrapper classes just serve as abstraction Layers
	 * to wrap around the chunk data. You can of course just use the chunk data
	 * directly if you want. This is just to make access to desired data more
	 * straight forward.
	 */
	class LIBSWBF2_API Level
	{

	typedef LibSWBF2::Chunks::LVL::LVL LVL;
	typedef LibSWBF2::Chunks::GenericBaseChunk GenericBaseChunk;
	typedef LibSWBF2::Chunks::LVL::skel::skel skel;


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
		List<Localization> m_Localizations;
		List<EntityClass> m_EntityClasses;
		List<AnimationBank> m_AnimationBanks;
		List<Sound> m_Sounds;
		List<Config> m_Configs;

		// fast pimpl to avoid inclusion of std::unordered_map
		class MapsWrapper* m_NameToIndexMaps;

	public:
		friend class Model;
		friend class Segment;

		// subLVLsToLoad doesn't need to be persistent, can be a stack value.
		// contents will be copied and hashed.
		static Level* FromFile(const String& path, const List<String>* subLVLsToLoad = nullptr);
		static Level* FromChunk(LVL* lvl, Container* mainContainer);
		static void Destroy(Level* level);

		const String& GetLevelPath() const;
		String GetLevelName() const;
		bool IsWorldLevel() const;

		const List<Model>& GetModels() const;
		const List<Texture>& GetTextures() const;
		const List<World>& GetWorlds() const;
		const List<Terrain>& GetTerrains() const;
		const List<Script>& GetScripts() const;
		const List<Localization>& GetLocalizations() const;
		const List<EntityClass>& GetEntityClasses() const;
		const List<AnimationBank>& GetAnimationBanks() const;
		const List<Sound>& GetSounds() const;
		const List<const Config *> GetConfigs(EConfigType cfgType = EConfigType::All) const;

		const Model* GetModel(const String& modelName) const;
		const Texture* GetTexture(const String& textureName) const;
		const World* GetWorld(const String& worldName) const;
		const Terrain* GetTerrain(const String& terrainName) const;
		const Script* GetScript(const String& scriptName) const;
		const Localization* GetLocalization(const String& loclName) const;
		const EntityClass* GetEntityClass(const String& typeName) const;
		const AnimationBank* GetAnimationBank(const String& setName) const;
		const Sound* GetSound(const String& soundName) const;
		const Sound* GetSound(FNVHash soundHashName) const;
		const Config* GetConfig(EConfigType cfgType, FNVHash hash) const;


	private:
		void ExploreChildrenRecursive(GenericBaseChunk* root);
		skel* FindSkeleton(const String& skeletonName) const;
	};
}
