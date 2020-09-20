// LibSWBF2.Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../LibSWBF2/LibSWBF2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <thread>
#include <chrono>

using LibSWBF2::Types::String;
using LibSWBF2::Types::List;
using LibSWBF2::Logging::Logger;
using LibSWBF2::Logging::LoggerEntry;
using LibSWBF2::LevelContainer;
using LibSWBF2::LevelHandle;

void libLog(const LoggerEntry* log)
{
	//std::cout << log->ToString().Buffer() << std::endl;
}

int main()
{
	Logger::SetLogCallback(&libLog);

	using Pair = std::pair<std::string, LevelHandle>;

	std::vector<Pair> handles;
	LevelContainer* levels = LevelContainer::Create();
	handles.emplace_back(Pair{ "geo1.lvl", levels->AddLevel("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Star Wars Battlefront II\\GameData\\data\\_lvl_pc\\geo\\geo1.lvl") });
	handles.emplace_back(Pair{ "rep.lvl", levels->AddLevel("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Star Wars Battlefront II\\GameData\\data\\_lvl_pc\\side\\rep.lvl") });
	handles.emplace_back(Pair{ "cis.lvl", levels->AddLevel("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Star Wars Battlefront II\\GameData\\data\\_lvl_pc\\side\\cis.lvl") });
	handles.emplace_back(Pair{ "common.lvl", levels->AddLevel("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Star Wars Battlefront II\\GameData\\data\\_lvl_pc\\common.lvl") });
	handles.emplace_back(Pair{ "ingame.lvl", levels->AddLevel("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Star Wars Battlefront II\\GameData\\data\\_lvl_pc\\ingame.lvl") });
	handles.emplace_back(Pair{ "mission.lvl", levels->AddLevel("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Star Wars Battlefront II\\GameData\\data\\_lvl_pc\\mission.lvl") });
	handles.emplace_back(Pair{ "shell.lvl", levels->AddLevel("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Star Wars Battlefront II\\GameData\\data\\_lvl_pc\\shell.lvl") });
	//handles.emplace_back(Pair{ "core.lvl", levels->AddLevel("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Star Wars Battlefront II\\GameData\\data\\_lvl_pc\\core.lvl") });

	std::cout << "Levels added." << std::endl;

	auto PrintProgress = [levels, &handles]()
	{
		int i = 0;
		for (Pair& handle : handles)
		{
			String status = LevelLoadStatusToString(levels->GetLevelStatus(handle.second));
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, (SHORT)i++ });
			std::cout << handle.first << ":\t" << " [" << status.Buffer() << "] " << levels->GetLevelProgress(handle.second) << "                      \n";
		}
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, (SHORT)i++ });
		std::cout << "Overall Progress: \t" << levels->GetOverallProgress() << "                                            \r";
	};

	levels->StartLoading();
	while (!levels->IsDone())
	{
		PrintProgress();
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
	PrintProgress();

	std::cout << "missionlist         : " << (levels->FindScript("missionlist") != nullptr ? "Found" : "NOT found") << std::endl;
	std::cout << "rep_inf_default     : " << (levels->FindEntityClass("rep_inf_default") != nullptr ? "Found" : "NOT found") << std::endl;

	uint16_t* data;
	uint32_t count;
	std::cout << "level.common.tips.1 : " << (levels->GetLocalizedWideString("english", "level.common.tips.1", data, count) ? "Found" : "NOT found") << std::endl;

	levels->FreeAll();

	return 0;
}