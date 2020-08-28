#include "LibSWBF2.h"
#include "FileWriter.h"
#include "Chunks/LVL/LVL.h"

#include <iostream>
#include <fstream>
#include <string>

using LibSWBF2::Types::String;
using LibSWBF2::Types::List;

using namespace LibSWBF2::Chunks::LVL;
using namespace LibSWBF2::Wrappers;

using LibSWBF2::Logging::Logger;
using LibSWBF2::Logging::LoggerEntry;


#define COUT(x) std::cout << x << std::endl



void libLog(const LoggerEntry* log){ COUT(log->ToString().Buffer()); }



int main()
{
	Logger::SetLogCallback(&libLog);

#ifdef __APPLE__
	Level *testLVL = Level::FromFile("/Users/will/Desktop/spotlightlvl/TST_spot_green.lvl");
#else
	Level *testLVL = Level::FromFile("/home/will/Desktop/light_types/TST_spot_white.lvl");
#endif

	return 0;
}
