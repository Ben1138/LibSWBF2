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
	Level *testLVL1 = Level::FromFile("/Users/will/Desktop/terrainblendinglvls/TST_Tex3_Blended.lvl");
	Level *testLVL2 = Level::FromFile("/Users/will/Desktop/terrainblendinglvls/TST_Tex3_Painted.lvl");
#else
	Level *testLVL = Level::FromFile("/home/will/Desktop/geo1.lvl");
#endif


	uint32_t width, height, elementSize;
	uint8_t *imgData;

	const Terrain& terr1 = testLVL1 -> GetTerrains()[0];
	terr1.GetSplatMap(width,height,elementSize,imgData);
	stbi_write_png("testsplat_blended.png", width, height, 4, reinterpret_cast<void *>(imgData), width*4);


	const Terrain& terr2 = testLVL2 -> GetTerrains()[0];
	terr2.GetSplatMap(width,height,elementSize,imgData);
	stbi_write_png("testsplat_painted.png", width, height, 4, reinterpret_cast<void *>(imgData), width*4);

	return 0;
}
