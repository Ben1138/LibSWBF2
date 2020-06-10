#include "stdafx.h"
#include "Level.h"
#include "Logging\Logger.h"
#include "Chunks\LVL\tex_\tex_.h"
#include "Chunks\LVL\modl\LVL.modl.h"

namespace LibSWBF2::Tools
{
	using Logging::ELogType;
	using Chunks::GenericBaseChunk;
	using Chunks::LVL::texture::tex_;
	using Chunks::LVL::modl::modl;

	// TODO: better solution than having a global hash map for all levels. cannot put in header aswell though...
	std::unordered_map<std::string, size_t> TextureNameToIndex;
	std::unordered_map<std::string, size_t> ModelNameToIndex;

	Level::Level(LVL* lvl)
	{
		p_lvl = lvl;
	}

	Level::~Level()
	{
		m_Models.Clear();
		m_Textures.Clear();

		if (p_lvl == nullptr)
		{
			LOG("p_lvl of Level was NULL!", ELogType::Error);
		}
		else
		{
			LVL::Destroy(p_lvl);
		}
	}

	Level* Level::FromFile(String path)
	{
		LVL* lvl = LVL::Create();
		if (!lvl->ReadFromFile(path.Buffer()))
		{
			LVL::Destroy(lvl);
			return nullptr;
		}
		
		Level* result = new Level(lvl);

		const List<GenericBaseChunk*>& children = lvl->GetChildren();
		for (size_t i = 0; i < children.Size(); ++i)
		{
			// IMPORTANT: crawl textures BEFORE models, so texture references via string can be resolved in models
			tex_* textureChunk = dynamic_cast<tex_*>(children[i]);
			if (textureChunk != nullptr)
			{
				Texture texture;
				if (Texture::FromChunk(textureChunk, texture))
				{
					TextureNameToIndex.emplace(texture.GetName().Buffer(), result->m_Textures.Add(texture));
				}
			}

			modl* modelChunk = dynamic_cast<modl*>(children[i]);
			if (modelChunk != nullptr)
			{
				Model model;
				if (Model::FromChunk(result, modelChunk, model))
				{
					ModelNameToIndex.emplace(model.GetName().Buffer(), result->m_Models.Add(model));
				}
			}
		}

		return result;
	}

	void Level::Destroy(Level* level)
	{
		if (level == nullptr)
		{
			LOG("Given level was NULL!", ELogType::Error);
			return;
		}

		delete level;
	}

	const List<Model>& Level::GetModels() const
	{
		return m_Models;
	}

	const List<Texture>& Level::GetTextures() const
	{
		return m_Textures;
	}

	const Model* Level::GetModel(String modelName) const
	{
		if (modelName == "")
		{
			return nullptr;
		}

		auto it = ModelNameToIndex.find(modelName.Buffer());
		if (it != ModelNameToIndex.end())
		{
			return &m_Models[it->second];
		}

		LOG("Could not find Model '" + string(modelName.Buffer()) + "'!", ELogType::Warning);
		return nullptr;
	}

	const Texture* Level::GetTexture(String textureName) const
	{
		if (textureName == "")
		{
			return nullptr;
		}

		auto it = TextureNameToIndex.find(textureName.Buffer());
		if (it != TextureNameToIndex.end())
		{
			return &m_Textures[it->second];
		}

		LOG("Could not find Texture '" + string(textureName.Buffer()) + "'!", ELogType::Warning);
		return nullptr;
	}
}