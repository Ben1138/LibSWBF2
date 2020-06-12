#pragma once
#include "req.h"
#include "Model.h"
#include "Texture.h"
#include "World.h"
#include "Types\LibString.h"
#include "Types\List.h"
#include "Chunks\LVL\LVL.h"

namespace LibSWBF2::Tools
{
	using Types::List;
	using Chunks::LVL::LVL;

	/*
	 * This and the other Tool classes just serve as another abstraction Layer
	 * to wrap around the chunk data. You can of course just use the chunk data
	 * directly if you want. This is just to make access to desired data more
	 * straight forward.
	 */
	class LIBSWBF2_EXP Level
	{
	private:
		Level(LVL* lvl);
		~Level();

	private:
		LVL* p_lvl;

		List<Model> m_Models;
		List<Texture> m_Textures;
		List<World> m_Worlds;

	public:
		static Level* FromFile(String path);
		static void Destroy(Level* level);

		const List<Model>& GetModels() const;
		const List<Texture>& GetTextures() const;
		const List<World>& GetWorlds() const;

		const Model* GetModel(String modelName) const;
		const Texture* GetTexture(String textureName) const;
		const World* GetWorld(String worldName) const;
	};
}