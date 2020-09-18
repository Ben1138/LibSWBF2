#include "stdafx.h"
#include "LevelContainer.h"
#include "InternalHelpers.h"
#include <vector>
#include <future>

namespace LibSWBF2
{
	struct LevelLoadStatus
	{
		ELevelLoadStatus m_LoadStatus = ELevelLoadStatus::Uninitialized;
		float_t m_Progress = 0.0f;
		Level* m_Level = nullptr;
	};

	class LevelContainerMembers
	{
	public:
		std::mutex m_StatusLock;
		std::vector<std::future<void>> m_Processes;
		std::vector<LevelLoadStatus> m_Statuses;
		std::vector<std::pair<String, const List<String>*>> m_ScheduledLevels;
	};

	void LevelContainer::LoadLevelAsync(size_t index, const String& path, const List<String>* subLVLsToLoad)
	{
		Level* level = Level::FromFile(path, subLVLsToLoad);

		std::lock_guard<std::mutex> lock(m_ThreadSafeMembers->m_StatusLock);
		m_ThreadSafeMembers->m_Statuses[index].m_Level = level;
		m_ThreadSafeMembers->m_Statuses[index].m_LoadStatus = level != nullptr ? ELevelLoadStatus::Loaded : ELevelLoadStatus::Failed;
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

	LevelHandle LevelContainer::ScheduleLevel(String path, const List<String>* subLVLsToLoad)
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

		size_t num = m_ThreadSafeMembers->m_ScheduledLevels.size();
		m_ThreadSafeMembers->m_Statuses.resize(num);
		for (size_t i = 0; num; ++i)
		{
			std::pair<String, const List<String>*>& scheduled = m_ThreadSafeMembers->m_ScheduledLevels[i];

			LevelLoadStatus& status = m_ThreadSafeMembers->m_Statuses[i];
			status.m_LoadStatus = ELevelLoadStatus::Loading;

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

		std::lock_guard<std::mutex> lock(m_ThreadSafeMembers->m_StatusLock);
		for (LevelLoadStatus& status : m_ThreadSafeMembers->m_Statuses)
		{
			if (status.m_Level != nullptr)
			{
				Level::Destroy(status.m_Level);
				status.m_Level = nullptr;
			}
		}
		m_ThreadSafeMembers->m_Statuses.clear();
		m_ThreadSafeMembers->m_Processes.clear();
		m_ThreadSafeMembers->m_ScheduledLevels.clear();
	}

	bool LevelContainer::IsDone() const
	{
		std::lock_guard<std::mutex> lock(m_ThreadSafeMembers->m_StatusLock);
		if (m_ThreadSafeMembers->m_Statuses.size() == 0)
		{
			return true;
		}

		bool bIsDone = true;
		for (LevelLoadStatus& status : m_ThreadSafeMembers->m_Statuses)
		{
			bIsDone = status.m_LoadStatus != ELevelLoadStatus::Loading && bIsDone;
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

		std::lock_guard<std::mutex> lock(m_ThreadSafeMembers->m_StatusLock);
		return m_ThreadSafeMembers->m_Statuses[handle].m_LoadStatus;
	}

	float_t LevelContainer::GetLevelProgress(LevelHandle handle) const
	{
		if (handle >= m_ThreadSafeMembers->m_Processes.size())
		{
			LOG_WARN("Given Level Handle '{}' is illegal!", handle);
			return 0.0f;
		}

		std::lock_guard<std::mutex> lock(m_ThreadSafeMembers->m_StatusLock);
		return m_ThreadSafeMembers->m_Statuses[handle].m_Progress;
	}

	Level* LevelContainer::GetLevel(LevelHandle handle) const
	{
		if (handle >= m_ThreadSafeMembers->m_Processes.size())
		{
			LOG_WARN("Given Level Handle '{}' is illegal!", handle);
			return nullptr;
		}

		std::lock_guard<std::mutex> lock(m_ThreadSafeMembers->m_StatusLock);
		return m_ThreadSafeMembers->m_Statuses[handle].m_Level;
	}
}