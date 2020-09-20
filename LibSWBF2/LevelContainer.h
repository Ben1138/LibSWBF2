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
	using LibSWBF2::Wrappers::Model;
	using LibSWBF2::Wrappers::Texture;
	using LibSWBF2::Wrappers::World;
	using LibSWBF2::Wrappers::Terrain;
	using LibSWBF2::Wrappers::Script;
	using LibSWBF2::Wrappers::Light;
	using LibSWBF2::Wrappers::Localization;
	using LibSWBF2::Wrappers::EntityClass;


	class LIBSWBF2_API LevelContainer
	{
	private:
		LevelContainer();
		~LevelContainer();

		class LevelContainerMembers* m_ThreadSafeMembers = nullptr;

		void LoadLevelAsync(size_t index, const String& path, const List<String>* subLVLsToLoad);
		uint64_t m_OverallSize = 0;

	public:
		static LevelContainer* Create();
		static void Delete(LevelContainer* instance);

		LevelHandle AddLevel(String path, const List<String>* subLVLsToLoad = nullptr);
		void StartLoading();
		void FreeAll();
		bool IsDone() const;
		ELevelLoadStatus GetLevelStatus(LevelHandle handle) const;
		float_t GetLevelProgress(LevelHandle handle) const;
		Level* GetLevel(LevelHandle handle) const;
		float_t GetOverallProgress();

		const Light* FindLight(String lightName) const;
		const Model* FindModel(String modelName) const;
		const Texture* FindTexture(String textureName) const;
		const World* FindWorld(String worldName) const;
		const Terrain* FindTerrain(String terrainName) const;
		const Script* FindScript(String scriptName) const;
		const Localization* FindLocalization(String loclName) const;
		const EntityClass* FindEntityClass(String typeName) const;

		// count is number of wide chars, NOT number of bytes!
		bool GetLocalizedWideString(const String& language, const String& path, uint16_t*& chars, uint32_t& count) const;
	};
}