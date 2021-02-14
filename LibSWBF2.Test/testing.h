#pragma once

#include "LibSWBF2.h"
#include "FileWriter.h"
#include "Chunks/LVL/LVL.h"
#include "Types/Enums.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <vector>

#include "fmt/core.h"
#include "fmt/format.h"


using LibSWBF2::Types::String;
using LibSWBF2::Types::List;

using namespace LibSWBF2::Chunks::LVL;
using namespace LibSWBF2::Wrappers;

using LibSWBF2::Container;
using LibSWBF2::SWBF2Handle;
using LibSWBF2::Logging::Logger;
using LibSWBF2::Logging::LoggerEntry;

#define COUT(x) std::cout << x << std::endl


Container * LoadAndTrackContainer(const List<String>& paths)
{
	Container *container = Container::Create();
	List<SWBF2Handle> handles;

	for (int i = 0; i < paths.Size(); i++)
	{
		handles.Add(container -> AddLevel(paths[i]));
	}

	container -> StartLoading();

	while (!container -> IsDone())
	{
		usleep(100000);
		
		std::cout << "\r";

		for (int i = 0; i < handles.Size(); i++)
		{
			std::cout << fmt::format("{}: {}% ", i, (int) (container -> GetLevelProgress(handles[i]) * 100.0f)).c_str();
		}

		std::cout << std::flush;
	}

	return container;
}



std::vector<const Level *> LoadAndTrackLVLs(List<String> paths, Container*& container)
{
	container = Container::Create();
	List<SWBF2Handle> handles;

	for (int i = 0; i < paths.Size(); i++)
	{
		handles.Add(container -> AddLevel(paths[i]));
	}

	container -> StartLoading();

	while (!container -> IsDone())
	{
		usleep(100000);
		
		std::cout << "\r";

		for (int i = 0; i < handles.Size(); i++)
		{
			std::cout << fmt::format("{}: {}% ", i, (int) (container -> GetLevelProgress(handles[i]) * 100.0f)).c_str();
		}

		std::cout << std::flush;

	}

	std::cout << std::endl;

	std::vector<const Level *> lvlPointers;

	for (int i = 0; i < handles.Size(); i++)
	{
		lvlPointers.push_back(container -> GetLevel(handles[i]));
	}

	return lvlPointers;
}





std::vector<const Level *> LoadAndTrackLVLs(List<String> paths)
{
	Container* container;
	return LoadAndTrackLVLs(paths, container);	
}







