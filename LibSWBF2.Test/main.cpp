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
using LibSWBF2::Container;
using LibSWBF2::SWBF2Handle;

void libLog(const LoggerEntry* log)
{
	//std::cout << log->ToString().Buffer() << std::endl;
}

int main()
{
	//Logger::SetLogCallback(&libLog);

	std::string path = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Star Wars Battlefront II\\GameData\\data\\_lvl_pc\\";
	using Pair = std::pair<std::string, SWBF2Handle>;

	std::vector<Pair> handles;
	Container* levels = Container::Create();
	handles.emplace_back(Pair{ "geo1.lvl",		levels->AddLevel((path + "geo\\geo1.lvl").c_str())			});
	handles.emplace_back(Pair{ "rep.lvl",		levels->AddLevel((path + "side\\rep.lvl").c_str())			});
	handles.emplace_back(Pair{ "cis.lvl",		levels->AddLevel((path + "side\\cis.lvl").c_str())			});
	handles.emplace_back(Pair{ "common.lvl",	levels->AddLevel((path + "common.lvl").c_str())				});
	handles.emplace_back(Pair{ "ingame.lvl",	levels->AddLevel((path + "ingame.lvl").c_str())				});
	handles.emplace_back(Pair{ "mission.lvl",	levels->AddLevel((path + "mission.lvl").c_str())			});
	handles.emplace_back(Pair{ "shell.lvl",		levels->AddLevel((path + "shell.lvl").c_str())				});
	handles.emplace_back(Pair{ "core.lvl",		levels->AddLevel((path + "core.lvl").c_str())				});
	handles.emplace_back(Pair{ "common.bnk",	levels->AddSoundBank((path + "sound\\common.bnk").c_str())	});

	std::cout << "Levels added." << std::endl;

	auto PrintProgress = [levels, &handles]()
	{
		int i = 0;
		for (Pair& handle : handles)
		{
			String status = LoadStatusToString(levels->GetStatus(handle.second));
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, (SHORT)i++ });
			std::cout << handle.first << ":\t" << " [" << status.Buffer() << "] " << round(levels->GetLevelProgress(handle.second) * 100.0f) << "%                      \n";
		}
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, (SHORT)i++ });
		std::cout << "Overall Progress: \t" << round(levels->GetOverallProgress() * 100.0f) << "%                                            \r";
	};

	levels->StartLoading();
	while (!levels->IsDone())
	{
		PrintProgress();
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
	PrintProgress();

	std::cout << "Trying to look up some data..." << std::endl;

	std::cout << "missionlist         : " << (levels->FindScript("missionlist") != nullptr ? "Found" : "NOT found") << std::endl;
	std::cout << "rep_inf_default     : " << (levels->FindEntityClass("rep_inf_default") != nullptr ? "Found" : "NOT found") << std::endl;
	std::cout << "ui_planetzoom       : " << (levels->FindSound("ui_planetzoom") != nullptr ? "Found" : "NOT found") << std::endl;

	uint16_t* data;
	uint32_t count;
	std::cout << "level.common.tips.1 : " << (levels->GetLocalizedWideString("german", "level.common.tips.1", data, count) ? "Found" : "NOT found") << std::endl;

	levels->FreeAll();

	return 0;
}