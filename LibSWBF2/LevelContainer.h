#pragma once
#include "Wrappers/Level.h"
#include "Types/LibString.h"
#include "Types/List.h"
#include "Types/Enums.h"

namespace LibSWBF2
{
	using LibSWBF2::Types::String;
	using LibSWBF2::Types::List;
	using LibSWBF2::Wrappers::Level;


	class LIBSWBF2_API LevelContainer
	{
	private:
		LevelContainer();
		~LevelContainer();

		class LevelContainerMembers* m_ThreadSafeMembers = nullptr;

		void LoadLevelAsync(size_t index, const String& path, const List<String>* subLVLsToLoad);

	public:
		static LevelContainer* Create();
		static void Delete(LevelContainer* instance);

		LevelHandle ScheduleLevel(String path, const List<String>* subLVLsToLoad = nullptr);
		void StartLoading();
		void FreeAll();
		bool IsDone() const;
		ELevelLoadStatus GetLevelStatus(LevelHandle handle) const;
		float_t GetLevelProgress(LevelHandle handle) const;
		Level* GetLevel(LevelHandle handle) const;
	};
}