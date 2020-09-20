#include "stdafx.h"
#include "LevelContainer.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include <vector>
#include <future>
#include <map>

namespace LibSWBF2
{
	using LibSWBF2::Chunks::LVL::LVL;

	struct LevelLoadStatus
	{
		ELevelLoadStatus m_LoadStatus = ELevelLoadStatus::Uninitialized;
		LVL* m_LVL = nullptr;
		Level* m_Level = nullptr;
		uint64_t m_FileSize = 0;
	};

	class LevelContainerMembers
	{
	public:
		std::mutex m_StatusLock;
		std::vector<std::future<void>> m_Processes;
		std::vector<LevelLoadStatus> m_Statuses;
		std::vector<std::pair<String, const List<String>*>> m_ScheduledLevels;

		// TODO: rework once we allow modifications (add / delete) in Levels
		std::unordered_map<std::string, const Texture*> TextureDB;
		std::unordered_map<std::string, const Model*> ModelDB;
		std::unordered_map<std::string, const World*> WorldDB;
		std::unordered_map<std::string, const Terrain*> TerrainDB;
		std::unordered_map<std::string, const Script*> ScriptDB;
		std::unordered_map<std::string, const Light*> LightDB;
		std::unordered_map<std::string, const Localization*> LocalizationDB;
		std::unordered_map<std::string, const EntityClass*> EntityClassDB;
	};

	template<class T>
	void CopyMap(std::unordered_map<std::string, size_t>& levelMap, const List<T>& list, std::unordered_map<std::string, const T*>& containerMap)
	{
		for (auto& it : levelMap)
		{
			containerMap.emplace(it.first, &list[it.second]);
		}
	}

	void LevelContainer::LoadLevelAsync(size_t index, const String& path, const List<String>* subLVLsToLoad)
	{
		LevelLoadStatus* status = nullptr;
		LVL* lvl = nullptr;
		{
			LOCK(m_ThreadSafeMembers->m_StatusLock);
			status = &m_ThreadSafeMembers->m_Statuses[index];

			FileReader reader;
			if (!reader.Open(path))
			{
				status->m_LoadStatus = ELevelLoadStatus::Failed;
				return;
			}
			else
			{
				status->m_FileSize = reader.GetFileSize();
				reader.Close();
			}

			lvl = LVL::Create();
			status->m_LVL = lvl;
			status->m_LoadStatus = ELevelLoadStatus::Loading;
		}

		if (lvl->ReadFromFile(path, subLVLsToLoad))
		{
			Level* level = Level::FromChunk(lvl, this);
			LOCK(m_ThreadSafeMembers->m_StatusLock);
			status->m_Level = level;
			if (level != nullptr)
			{
				CopyMap(level->m_NameToIndexMaps->TextureNameToIndex,		level->m_Textures,		m_ThreadSafeMembers->TextureDB);
				CopyMap(level->m_NameToIndexMaps->ModelNameToIndex,			level->m_Models,		m_ThreadSafeMembers->ModelDB);
				CopyMap(level->m_NameToIndexMaps->WorldNameToIndex,			level->m_Worlds,		m_ThreadSafeMembers->WorldDB);
				CopyMap(level->m_NameToIndexMaps->ScriptNameToIndex,		level->m_Scripts,		m_ThreadSafeMembers->ScriptDB);
				CopyMap(level->m_NameToIndexMaps->LightNameToIndex,			level->m_Lights,		m_ThreadSafeMembers->LightDB);
				CopyMap(level->m_NameToIndexMaps->LocalizationNameToIndex,	level->m_Localizations,	m_ThreadSafeMembers->LocalizationDB);
				CopyMap(level->m_NameToIndexMaps->EntityClassTypeToIndex,	level->m_EntityClasses, m_ThreadSafeMembers->EntityClassDB);
				status->m_LoadStatus = ELevelLoadStatus::Loaded;
			}
			else
			{
				status->m_LoadStatus = ELevelLoadStatus::Failed;
				LVL::Destroy(lvl);
			}
		}
		else
		{
			LOCK(m_ThreadSafeMembers->m_StatusLock);
			status->m_LoadStatus = ELevelLoadStatus::Failed;
			LVL::Destroy(lvl);
		}
		status->m_LVL = nullptr;
	}

	LevelContainer::LevelContainer()
	{
		m_ThreadSafeMembers = new LevelContainerMembers();
	}

	LevelContainer::~LevelContainer()
	{
		FreeAll();
		delete m_ThreadSafeMembers;
		m_ThreadSafeMembers = nullptr;
	}

	LevelContainer* LevelContainer::Create()
	{
		return new LevelContainer();
	}

	void LevelContainer::Delete(LevelContainer* instance)
	{
		delete instance;
	}

	LevelHandle LevelContainer::AddLevel(String path, const List<String>* subLVLsToLoad)
	{
		m_ThreadSafeMembers->m_ScheduledLevels.push_back({ path, subLVLsToLoad });
		return (LevelHandle)m_ThreadSafeMembers->m_ScheduledLevels.size() - 1;
	}

	void LevelContainer::StartLoading()
	{
		if (m_ThreadSafeMembers->m_Processes.size() > 0)
		{
			LOG_WARN("Already running!");
			return;
		}
		if (m_ThreadSafeMembers->m_ScheduledLevels.size() == 0)
		{
			LOG_WARN("No levels scheduled to load!");
			return;
		}

		m_OverallSize = 0;
		LOCK(m_ThreadSafeMembers->m_StatusLock);
		size_t num = m_ThreadSafeMembers->m_ScheduledLevels.size();

		m_ThreadSafeMembers->m_Statuses.clear();
		for (size_t i = 0; i < num; ++i)
		{
			m_ThreadSafeMembers->m_Statuses.emplace_back();
			std::pair<String, const List<String>*>& scheduled = m_ThreadSafeMembers->m_ScheduledLevels[i];
			m_ThreadSafeMembers->m_Processes.push_back(std::async(std::launch::async, &LevelContainer::LoadLevelAsync, this, i, scheduled.first, scheduled.second));
		}
		m_ThreadSafeMembers->m_ScheduledLevels.clear();		
	}

	void LevelContainer::FreeAll()
	{
		if (m_ThreadSafeMembers->m_Processes.size() == 0)
		{
			LOG_WARN("Nothing to free!");
			return;
		}

		if (!IsDone())
		{
			LOG_WARN("Cannot free while still running!");
			return;
		}

		{
			LOCK(m_ThreadSafeMembers->m_StatusLock);
			for (LevelLoadStatus& status : m_ThreadSafeMembers->m_Statuses)
			{
				if (status.m_Level != nullptr)
				{
					Level::Destroy(status.m_Level);
					status.m_Level = nullptr;
				}
			}
		}
		
		delete m_ThreadSafeMembers;
		m_ThreadSafeMembers = new LevelContainerMembers();
	}

	bool LevelContainer::IsDone() const
	{
		LOCK(m_ThreadSafeMembers->m_StatusLock);
		if (m_ThreadSafeMembers->m_Statuses.size() == 0)
		{
			return true;
		}

		bool bIsDone = true;
		for (LevelLoadStatus& status : m_ThreadSafeMembers->m_Statuses)
		{
			bIsDone = status.m_LoadStatus != ELevelLoadStatus::Loading && status.m_LoadStatus != ELevelLoadStatus::Uninitialized && bIsDone;
		}
		return bIsDone;
	}

	ELevelLoadStatus LevelContainer::GetLevelStatus(LevelHandle handle) const
	{
		if (handle >= m_ThreadSafeMembers->m_Processes.size())
		{
			LOG_WARN("Given Level Handle '{}' is illegal!", handle);
			return ELevelLoadStatus::Uninitialized;
		}

		LOCK(m_ThreadSafeMembers->m_StatusLock);
		return m_ThreadSafeMembers->m_Statuses[handle].m_LoadStatus;
	}

	float_t LevelContainer::GetLevelProgress(LevelHandle handle) const
	{
		if (handle >= m_ThreadSafeMembers->m_Processes.size())
		{
			LOG_WARN("Given Level Handle '{}' is illegal!", handle);
			return 0.0f;
		}

		LOCK(m_ThreadSafeMembers->m_StatusLock);
		LevelLoadStatus& status = m_ThreadSafeMembers->m_Statuses[handle];
		if (status.m_LVL == nullptr)
		{
			return 1.0f;
		}
		return status.m_LVL->GetReadingProgress();
	}

	Level* LevelContainer::GetLevel(LevelHandle handle) const
	{
		if (handle >= m_ThreadSafeMembers->m_Processes.size())
		{
			LOG_WARN("Given Level Handle '{}' is illegal!", handle);
			return nullptr;
		}

		LOCK(m_ThreadSafeMembers->m_StatusLock);
		return m_ThreadSafeMembers->m_Statuses[handle].m_Level;
	}

	float_t LevelContainer::GetOverallProgress()
	{
		LOCK(m_ThreadSafeMembers->m_StatusLock);
		size_t num = m_ThreadSafeMembers->m_Statuses.size();
		if (m_OverallSize == 0)
		{
			for (size_t i = 0; i < num; ++i)
			{
				LevelLoadStatus& status = m_ThreadSafeMembers->m_Statuses[i];
				if (status.m_LoadStatus == ELevelLoadStatus::Uninitialized)
				{
					// wait until all tasks started
					m_OverallSize = 0;
					return 0.0f;
				}
				m_OverallSize += status.m_FileSize;
			}
		}

		float_t progress = 0.0f;
		for (size_t i = 0; i < num; ++i)
		{
			LevelLoadStatus& status = m_ThreadSafeMembers->m_Statuses[i];
			if (status.m_FileSize > 0)
			{
				float lvlProgress = status.m_LVL != nullptr ? status.m_LVL->GetReadingProgress() : 1.0f;
				lvlProgress *= status.m_FileSize / (float_t)m_OverallSize;
				progress += lvlProgress;
			}
		}
		return progress;
	}

	const Light* LevelContainer::FindLight(String lightName) const
	{
		if (!IsDone())
		{
			LOG_WARN("Cannot lookup Light '{}' while still loading!");
			return nullptr;
		}
		if (lightName.IsEmpty())
		{
			return nullptr;
		}

		auto it = m_ThreadSafeMembers->LightDB.find(ToLower(lightName));
		if (it != m_ThreadSafeMembers->LightDB.end())
		{
			return it->second;
		}

		return nullptr;
	}

	const Model* LevelContainer::FindModel(String modelName) const
	{
		if (!IsDone())
		{
			LOG_WARN("Cannot lookup Light '{}' while still loading!");
			return nullptr;
		}
		if (modelName.IsEmpty())
		{
			return nullptr;
		}

		auto it = m_ThreadSafeMembers->ModelDB.find(ToLower(modelName));
		if (it != m_ThreadSafeMembers->ModelDB.end())
		{
			return it->second;
		}

		return nullptr;
	}

	const Texture* LevelContainer::FindTexture(String textureName) const
	{
		if (!IsDone())
		{
			LOG_WARN("Cannot lookup Light '{}' while still loading!");
			return nullptr;
		}
		if (textureName.IsEmpty())
		{
			return nullptr;
		}

		auto it = m_ThreadSafeMembers->TextureDB.find(ToLower(textureName));
		if (it != m_ThreadSafeMembers->TextureDB.end())
		{
			return it->second;
		}

		return nullptr;
	}

	const World* LevelContainer::FindWorld(String worldName) const
	{
		if (!IsDone())
		{
			LOG_WARN("Cannot lookup Light '{}' while still loading!");
			return nullptr;
		}
		if (worldName.IsEmpty())
		{
			return nullptr;
		}

		auto it = m_ThreadSafeMembers->WorldDB.find(ToLower(worldName));
		if (it != m_ThreadSafeMembers->WorldDB.end())
		{
			return it->second;
		}

		return nullptr;
	}

	const Terrain* LevelContainer::FindTerrain(String terrainName) const
	{
		if (!IsDone())
		{
			LOG_WARN("Cannot lookup Light '{}' while still loading!");
			return nullptr;
		}
		if (terrainName.IsEmpty())
		{
			return nullptr;
		}

		auto it = m_ThreadSafeMembers->TerrainDB.find(ToLower(terrainName));
		if (it != m_ThreadSafeMembers->TerrainDB.end())
		{
			return it->second;
		}

		return nullptr;
	}

	const Script* LevelContainer::FindScript(String scriptName) const
	{
		if (!IsDone())
		{
			LOG_WARN("Cannot lookup Light '{}' while still loading!");
			return nullptr;
		}
		if (scriptName.IsEmpty())
		{
			return nullptr;
		}

		auto it = m_ThreadSafeMembers->ScriptDB.find(ToLower(scriptName));
		if (it != m_ThreadSafeMembers->ScriptDB.end())
		{
			return it->second;
		}

		return nullptr;
	}

	const Localization* LevelContainer::FindLocalization(String loclName) const
	{
		if (!IsDone())
		{
			LOG_WARN("Cannot lookup Light '{}' while still loading!");
			return nullptr;
		}
		if (loclName.IsEmpty())
		{
			return nullptr;
		}

		auto it = m_ThreadSafeMembers->LocalizationDB.find(ToLower(loclName));
		if (it != m_ThreadSafeMembers->LocalizationDB.end())
		{
			return it->second;
		}

		return nullptr;
	}

	const EntityClass* LevelContainer::FindEntityClass(String typeName) const
	{
		if (!IsDone())
		{
			LOG_WARN("Cannot lookup Light '{}' while still loading!");
			return nullptr;
		}
		if (typeName.IsEmpty())
		{
			return nullptr;
		}

		auto it = m_ThreadSafeMembers->EntityClassDB.find(ToLower(typeName));
		if (it != m_ThreadSafeMembers->EntityClassDB.end())
		{
			return it->second;
		}

		return nullptr;
	}

	bool LevelContainer::GetLocalizedWideString(const String& language, const String& path, uint16_t*& chars, uint32_t& count) const
	{
		const Localization* local = FindLocalization(language);
		if (local == nullptr)
		{
			LOG_WARN("Cannot find language '{}'!", language);
			return false;
		}
		return local->GetLocalizedWideString(path, chars, count);
	}
}