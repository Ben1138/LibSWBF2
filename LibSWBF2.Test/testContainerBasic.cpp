#include "LibSWBF2.h"
#include "FileWriter.h"
#include "Chunks/LVL/LVL.h"
#include "Types/Enums.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

#include "fmt/core.h"
#include "fmt/format.h"


using LibSWBF2::Types::String;
using LibSWBF2::Types::List;

using namespace LibSWBF2::Chunks::LVL;
using namespace LibSWBF2::Wrappers;

using LibSWBF2::Container;
using LibSWBF2::Logging::Logger;
using LibSWBF2::Logging::LoggerEntry;


#define COUT(x) std::cout << x << std::endl

//void libLog(const LoggerEntry* log){ COUT(log->ToString().Buffer()); }



int main()
{
	//Logger::SetLogCallback(&libLog);

	const char *path1;
	const char *path2;

#ifdef __APPLE__
	path1 = "/Users/will/Desktop/geo1.lvl";
	path2 = "/Users/will/Desktop/MLC.lvl";
#else
	path1 = "/home/will/Desktop/geo1.lvl";
	path2 = "/home/will/Desktop/MLC.lvl";
#endif

	Container *container = Container::Create();
	auto handle1 = container -> AddLevel(path1);
	auto handle2 = container -> AddLevel(path2);
	container -> StartLoading();

	while (!container -> IsDone())
	{
		usleep(100000);
		std::cout << fmt::format("\rProgress1: {}%, Progress2: {}%", 
								(int) (container -> GetLevelProgress(handle1) * 100.0f),
								(int) (container -> GetLevelProgress(handle2) * 100.0f)).c_str()
				  << std::flush;
	}

	std::cout << std::endl;
	
	return 0;
}
