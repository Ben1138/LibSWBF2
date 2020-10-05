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


int main()
{
#ifdef __APPLE__
	Level *testLVL = Level::FromFile("/Users/will/Desktop/MLC.lvl");
	//Level *testLVL = Level::FromFile("/Users/will/Desktop/lght_layers/TST_L1Lyr2_globalchanges.lvl");
#else
	Level *testLVL = Level::FromFile("/home/will/Desktop/light_types/TST_spot_white.lvl");
#endif

	COUT(testLVL -> GetGlobalLighting() -> ToString().Buffer());

	const List<Light>& lights = testLVL -> GetLights();

	for (int i = 0; i < lights.Size(); i++)
	{
		Light lighti = lights[i];
		COUT(lighti.ToString().Buffer());
	}

	return 0;
}
