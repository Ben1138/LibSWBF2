#include "LibSWBF2.h"
#include "FileWriter.h"
#include "Chunks/LVL/LVL.h"

#include <iostream>
#include <fstream>
#include <string>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stbi/stb_image_write.h"

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
	Level *testLVL = Level::FromFile("/Users/will/Desktop/terrainblendinglvls/TST_Square_Tex1_Tex2_Blended.lvl");
#else
	Level *testLVL = Level::FromFile("/home/will/Desktop/geo1.lvl");
#endif

	const Terrain& terr = testLVL -> GetTerrains()[0];

	uint32_t width, height, elementSize;
	uint8_t *imgData;

	terr.GetSplatMap(width,height,elementSize,imgData);

	stbi_write_png("testsplat.png", width, height, 4, reinterpret_cast<void *>(imgData), width*4);


	return 0;
}
