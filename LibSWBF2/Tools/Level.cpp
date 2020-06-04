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

	Level::Level(LVL* lvl)
	{
		p_lvl = lvl;
	}

	Level::~Level()
	{
		for (size_t i = 0; i < m_Models.Size(); ++i)
		{
			Model::Destroy(m_Models[i]);
		}
		m_Models.Clear();

		for (size_t i = 0; i < m_Textures.Size(); ++i)
		{
			Texture::Destroy(m_Textures[i]);
		}
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
			modl* modelChunk = dynamic_cast<modl*>(children[i]);
			if (modelChunk != nullptr)
			{
				result->m_Models.Add(Model::FromChunk(result, modelChunk));
			}

			tex_* textureChunk = dynamic_cast<tex_*>(children[i]);
			if (textureChunk != nullptr)
			{
				result->m_Textures.Add(Texture::FromChunk(textureChunk));
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

	const List<Model*>& Level::GetModels() const
	{
		return m_Models;
	}

	const List<Texture*>& Level::GetTextures() const
	{
		return m_Textures;
	}
}