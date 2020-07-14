#pragma once
#include "req.h"
#include "Model.h"
#include "Texture.h"
#include "World.h"
#include "Terrain.h"
#include "Script.h"
#include "Types/LibString.h"
#include "Types/List.h"
#include "Chunks/LVL/LVL.h"


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
		Level(LVL* lvl);
		~Level();

	private:
		LVL* p_lvl;

		List<Model> m_Models;
		List<Texture> m_Textures;
		List<World> m_Worlds;
		List<Terrain> m_Terrains;	// multiple terrains are possible, in theory. never saw it though
		List<Script> m_Scripts;

		// fast pimpl to avoid inclusion of std::unordered_map
		class MapsWrapper* m_NameToIndexMaps;

	public:
		static Level* FromFile(String path);
		static void Destroy(Level* level);

		const List<Model>& GetModels() const;
		const List<Texture>& GetTextures() const;
		const List<World>& GetWorlds() const;
		const List<Terrain>& GetTerrains() const;
		const List<Script>& GetScripts() const;

		const Model* GetModel(String modelName) const;
		const Texture* GetTexture(String textureName) const;
		const World* GetWorld(String worldName) const;
		const Terrain* GetTerrain(String terrainName) const;
		const Script* GetScript(String scriptName) const;

	private:
		void FindInChildrenRecursive(GenericBaseChunk* root);
	};
}