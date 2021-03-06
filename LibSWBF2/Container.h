#pragma once
#include "Wrappers/Level.h"
#include "Wrappers/Terrain.h"
#include "Wrappers/Localization.h"
#include "Wrappers/SoundBank.h"
#include "Types/LibString.h"
#include "Types/List.h"
#include "Types/Enums.h"

namespace LibSWBF2
{
	using LibSWBF2::Types::String;
	using LibSWBF2::Types::List;
	using LibSWBF2::Wrappers::Level;
	using LibSWBF2::Wrappers::SoundBank;
	using LibSWBF2::Wrappers::Sound;
	using LibSWBF2::Wrappers::Model;
	using LibSWBF2::Wrappers::Texture;
	using LibSWBF2::Wrappers::World;
	using LibSWBF2::Wrappers::Terrain;
	using LibSWBF2::Wrappers::Script;
	using LibSWBF2::Wrappers::Localization;
	using LibSWBF2::Wrappers::EntityClass;
	using LibSWBF2::Wrappers::AnimationBank;
	using LibSWBF2::Wrappers::Config;

	struct Schedule
	{
		SWBF2Handle m_Handle;
		String m_Path;
		List<String> m_SubLVLsToLoad;
		bool m_bIsSoundBank = false;
		bool bRegisterContents = true;
	};

	// Procedure:
	// - Schedule levels and sound banks to load via AddLevel / AddSoundBank
	// - Call StartLoading();
	// - Repeat as many times as you want. Also possible while loading.
	class LIBSWBF2_API Container
	{
	private:
		Container();
		~Container();

		class ContainerMembers* m_ThreadSafeMembers = nullptr;
		uint64_t m_OverallSize = 0;

		void LoadLevelAsync(const Schedule& scheduled);
		void LoadSoundBankAsync(const Schedule& scheduled);

	public:
		static Container* Create();
		static void Delete(Container* instance);

		SWBF2Handle AddLevel(const String& path, const List<String>* subLVLsToLoad = nullptr, bool bRegisterContents=true);
		SWBF2Handle AddSoundBank(const String& path, bool bRegisterContents = true);
		void StartLoading();
		void FreeAll(bool bForce=false);
		bool IsDone() const;
		List<SWBF2Handle> GetLoadedLevels() const;
		ELoadStatus GetStatus(SWBF2Handle handle) const;
		float_t GetLevelProgress(SWBF2Handle handle) const;
		Level* GetLevel(SWBF2Handle handle) const;
		float_t GetOverallProgress();

		// will return the first encountered world LVL, if existent
		Level* TryGetWorldLevel() const;

		const List<const World*>& GetWorlds();

		//const Light* FindLight(String lightName) const;
		const Model* FindModel(String modelName) const;
		const Texture* FindTexture(String textureName) const;
		const World* FindWorld(String worldName) const;
		const Terrain* FindTerrain(String terrainName) const;
		const Script* FindScript(String scriptName) const;
		const EntityClass* FindEntityClass(String typeName) const;
		const Sound* FindSound(String soundName) const;
		const Sound* FindSound(FNVHash hashedSoundName) const;
		const AnimationBank* FindAnimationBank(String setName) const;

		const Config* FindConfig(EConfigType type, FNVHash hashedConfigName) const;

		const List<const Localization*>* FindLocalizations(String languageName) const;
		// count is number of wide chars, NOT number of bytes!
		bool GetLocalizedWideString(const String& language, const String& path, uint16_t*& chars, uint32_t& count) const;
	};
}