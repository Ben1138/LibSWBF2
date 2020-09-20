#include "stdafx.h"
#include "Container.h"
#include "InternalHelpers.h"
#include "Hashing.h"
#include "FileReader.h"
#include "Chunks/BNK/BNK.h"
#include <vector>
#include <future>
#include <map>

namespace LibSWBF2
{
	using LibSWBF2::Chunks::GenericBaseChunk;
	using LibSWBF2::Chunks::LVL::LVL;
	using LibSWBF2::Chunks::BNK::BNK;

	struct LoadStatus
	{
		ELoadStatus m_LoadStatus = ELoadStatus::Uninitialized;
		GenericBaseChunk* m_Chunk = nullptr;
		Level* m_Level = nullptr;
		SoundBank* m_SoundBank = nullptr;
		uint64_t m_FileSize = 0;
	};

	struct Schedule
	{
		String m_Path;
		const List<String>* m_SubLVLsToLoad = nullptr;
		bool m_bIsSoundBank = false;
	};

	class ContainerMembers
	{
	public:
		std::mutex m_StatusLock;
		std::vector<std::future<void>> m_Processes;
		std::vector<LoadStatus> m_Statuses;
		std::vector<Schedule> m_Scheduled;

		// TODO: rework once we allow modifications (add / delete) in Levels
		std::unordered_map<std::string, const Texture*> TextureDB;
		std::unordered_map<std::string, const Model*> ModelDB;
		std::unordered_map<std::string, const World*> WorldDB;
		std::unordered_map<std::string, const Terrain*> TerrainDB;
		std::unordered_map<std::string, const Script*> ScriptDB;
		std::unordered_map<std::string, const Light*> LightDB;
		std::unordered_map<std::string, const Localization*> LocalizationDB;
		std::unordered_map<std::string, const EntityClass*> EntityClassDB;
		std::unordered_map<FNVHash, const Sound*> SoundDB;
	};

	template<class T1, class T2>
	void CopyMap(std::unordered_map<T2, size_t>& levelMap, const List<T1>& list, std::unordered_map<T2, const T1*>& containerMap)
	{
		for (auto& it : levelMap)
		{
			containerMap.emplace(it.first, &list[it.second]);
		}
	}

	void Container::LoadLevelAsync(size_t index, const String& path, const List<String>* subLVLsToLoad)
	{
		LoadStatus* status = nullptr;
		LVL* lvl = nullptr;
		{
			LOCK(m_ThreadSafeMembers->m_StatusLock);
			status = &m_ThreadSafeMembers->m_Statuses[index];

			FileReader reader;
			if (!reader.Open(path))
			{
				status->m_LoadStatus = ELoadStatus::Failed;
				return;
			}
			else
			{
				status->m_FileSize = reader.GetFileSize();
				reader.Close();
			}

			lvl = LVL::Create();
			status->m_Chunk = lvl;
			status->m_LoadStatus = ELoadStatus::Loading;
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
				CopyMap(level->m_NameToIndexMaps->LocalizationNameToIndex,	level->m_Localizations, m_ThreadSafeMembers->LocalizationDB);
				CopyMap(level->m_NameToIndexMaps->EntityClassTypeToIndex,	level->m_EntityClasses, m_ThreadSafeMembers->EntityClassDB);
				status->m_LoadStatus = ELoadStatus::Loaded;
			}
			else
			{
				status->m_LoadStatus = ELoadStatus::Failed;
				LVL::Destroy(lvl);
			}
		}
		else
		{
			LOCK(m_ThreadSafeMembers->m_StatusLock);
			status->m_LoadStatus = ELoadStatus::Failed;
			LVL::Destroy(lvl);
		}
		status->m_Chunk = nullptr;
	}

	void Container::LoadSoundBankAsync(size_t index, const String& path)
	{
		LoadStatus* status = nullptr;
		BNK* bnk = nullptr;
		{
			LOCK(m_ThreadSafeMembers->m_StatusLock);
			status = &m_ThreadSafeMembers->m_Statuses[index];

			FileReader reader;
			if (!reader.Open(path))
			{
				status->m_LoadStatus = ELoadStatus::Failed;
				return;
			}
			else
			{
				status->m_FileSize = reader.GetFileSize();
				reader.Close();
			}

			bnk = BNK::Create();
			status->m_Chunk = bnk;
			status->m_LoadStatus = ELoadStatus::Loading;
		}

		if (bnk->ReadFromFile(path))
		{
			SoundBank* soundBank = SoundBank::FromChunk(bnk);
			LOCK(m_ThreadSafeMembers->m_StatusLock);
			status->m_SoundBank = soundBank;
			if (soundBank != nullptr)
			{
				CopyMap(soundBank->m_NameToIndexMaps->SoundHashToIndex, soundBank->m_Sounds, m_ThreadSafeMembers->SoundDB);
				status->m_LoadStatus = ELoadStatus::Loaded;
			}
			else
			{
				status->m_LoadStatus = ELoadStatus::Failed;
				BNK::Destroy(bnk);
			}
		}
		else
		{
			LOCK(m_ThreadSafeMembers->m_StatusLock);
			status->m_LoadStatus = ELoadStatus::Failed;
			BNK::Destroy(bnk);
		}
		status->m_Chunk = nullptr;
	}

	Container::Container()
	{
		m_ThreadSafeMembers = new ContainerMembers();
	}

	Container::~Container()
	{
		FreeAll();
		delete m_ThreadSafeMembers;
		m_ThreadSafeMembers = nullptr;
	}

	Container* Container::Create()
	{
		return new Container();
	}

	void Container::Delete(Container* instance)
	{
		delete instance;
	}

	SWBF2Handle Container::AddLevel(const String& path, const List<String>* subLVLsToLoad)
	{
		m_ThreadSafeMembers->m_Scheduled.push_back({ path, subLVLsToLoad, false });
		return (SWBF2Handle)m_ThreadSafeMembers->m_Scheduled.size() - 1;
	}

	SWBF2Handle Container::AddSoundBank(const String& path)
	{
		m_ThreadSafeMembers->m_Scheduled.push_back({ path, nullptr, true });
		return (SWBF2Handle)m_ThreadSafeMembers->m_Scheduled.size() - 1;
	}

	void Container::StartLoading()
	{
		if (m_ThreadSafeMembers->m_Processes.size() > 0)
		{
			LOG_WARN("Already running!");
			return;
		}
		if (m_ThreadSafeMembers->m_Scheduled.size() == 0)
		{
			LOG_WARN("No levels scheduled to load!");
			return;
		}

		m_OverallSize = 0;
		LOCK(m_ThreadSafeMembers->m_StatusLock);
		size_t num = m_ThreadSafeMembers->m_Scheduled.size();

		m_ThreadSafeMembers->m_Statuses.clear();
		for (size_t i = 0; i < num; ++i)
		{
			m_ThreadSafeMembers->m_Statuses.emplace_back();
			Schedule& scheduled = m_ThreadSafeMembers->m_Scheduled[i];
			if (scheduled.m_bIsSoundBank)
			{
				m_ThreadSafeMembers->m_Processes.push_back(std::async(std::launch::async, &Container::LoadSoundBankAsync, this, i, scheduled.m_Path));
			}
			else
			{
				m_ThreadSafeMembers->m_Processes.push_back(std::async(std::launch::async, &Container::LoadLevelAsync, this, i, scheduled.m_Path, scheduled.m_SubLVLsToLoad));
			}
		}
		m_ThreadSafeMembers->m_Scheduled.clear();
	}

	void Container::FreeAll()
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
			for (LoadStatus& status : m_ThreadSafeMembers->m_Statuses)
			{
				if (status.m_Level != nullptr)
				{
					Level::Destroy(status.m_Level);
					status.m_Level = nullptr;
				}
				if (status.m_SoundBank != nullptr)
				{
					SoundBank::Destroy(status.m_SoundBank);
					status.m_SoundBank = nullptr;
				}
			}
		}

		delete m_ThreadSafeMembers;
		m_ThreadSafeMembers = new ContainerMembers();
	}

	bool Container::IsDone() const
	{
		LOCK(m_ThreadSafeMembers->m_StatusLock);
		if (m_ThreadSafeMembers->m_Statuses.size() == 0)
		{
			return true;
		}

		bool bIsDone = true;
		for (LoadStatus& status : m_ThreadSafeMembers->m_Statuses)
		{
			bIsDone = status.m_LoadStatus != ELoadStatus::Loading && status.m_LoadStatus != ELoadStatus::Uninitialized && bIsDone;
		}
		return bIsDone;
	}

	ELoadStatus Container::GetLevelStatus(SWBF2Handle handle) const
	{
		if (handle >= m_ThreadSafeMembers->m_Processes.size())
		{
			LOG_WARN("Given Level Handle '{}' is illegal!", handle);
			return ELoadStatus::Uninitialized;
		}

		LOCK(m_ThreadSafeMembers->m_StatusLock);
		return m_ThreadSafeMembers->m_Statuses[handle].m_LoadStatus;
	}

	float_t Container::GetLevelProgress(SWBF2Handle handle) const
	{
		if (handle >= m_ThreadSafeMembers->m_Processes.size())
		{
			LOG_WARN("Given Level Handle '{}' is illegal!", handle);
			return 0.0f;
		}

		LOCK(m_ThreadSafeMembers->m_StatusLock);
		LoadStatus& status = m_ThreadSafeMembers->m_Statuses[handle];
		if (status.m_LoadStatus != ELoadStatus::Loading)
		{
			return 1.0f;
		}
		return status.m_Chunk->GetReadingProgress();
	}

	Level* Container::GetLevel(SWBF2Handle handle) const
	{
		if (handle >= m_ThreadSafeMembers->m_Processes.size())
		{
			LOG_WARN("Given Level Handle '{}' is illegal!", handle);
			return nullptr;
		}

		LOCK(m_ThreadSafeMembers->m_StatusLock);
		return m_ThreadSafeMembers->m_Statuses[handle].m_Level;
	}

	float_t Container::GetOverallProgress()
	{
		LOCK(m_ThreadSafeMembers->m_StatusLock);
		size_t num = m_ThreadSafeMembers->m_Statuses.size();
		if (m_OverallSize == 0)
		{
			for (size_t i = 0; i < num; ++i)
			{
				LoadStatus& status = m_ThreadSafeMembers->m_Statuses[i];
				if (status.m_LoadStatus == ELoadStatus::Uninitialized)
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
			LoadStatus& status = m_ThreadSafeMembers->m_Statuses[i];
			if (status.m_FileSize > 0)
			{
				float lvlProgress = status.m_Chunk != nullptr ? status.m_Chunk->GetReadingProgress() : 1.0f;
				lvlProgress *= status.m_FileSize / (float_t)m_OverallSize;
				progress += lvlProgress;
			}
		}
		return progress;
	}

	const Light* Container::FindLight(String lightName) const
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

	const Model* Container::FindModel(String modelName) const
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

	const Texture* Container::FindTexture(String textureName) const
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

	const World* Container::FindWorld(String worldName) const
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

	const Terrain* Container::FindTerrain(String terrainName) const
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

	const Script* Container::FindScript(String scriptName) const
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

	const Localization* Container::FindLocalization(String loclName) const
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

	const EntityClass* Container::FindEntityClass(String typeName) const
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

	const Sound* Container::FindSound(String soundName) const
	{
		if (!IsDone())
		{
			LOG_WARN("Cannot lookup Light '{}' while still loading!");
			return nullptr;
		}
		if (soundName.IsEmpty())
		{
			return nullptr;
		}
		return FindSound(FNV::Hash(soundName));
	}

	const Sound* Container::FindSound(FNVHash hashedSoundName) const
	{
		if (!IsDone())
		{
			LOG_WARN("Cannot lookup Light '{}' while still loading!");
			return nullptr;
		}

		auto it = m_ThreadSafeMembers->SoundDB.find(hashedSoundName);
		if (it != m_ThreadSafeMembers->SoundDB.end())
		{
			return it->second;
		}

		return nullptr;
	}

	bool Container::GetLocalizedWideString(const String& language, const String& path, uint16_t*& chars, uint32_t& count) const
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