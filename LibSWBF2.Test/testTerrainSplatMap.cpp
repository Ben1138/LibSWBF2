#include "../LibSWBF2/LibSWBF2.h"
#include "../LibSWBF2/FileWriter.h"
#include "../LibSWBF2/Chunks/LVL/LVL.h"

#include <iostream>
#include <fstream>
#include <string>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stbi/stb_image_write.h"

using LibSWBF2::Types::String;
using LibSWBF2::Types::List;

using namespace LibSWBF2::Wrappers;

using LibSWBF2::Logging::Logger;
using LibSWBF2::Logging::LoggerEntry;


#define COUT(x) std::cout << x << std::endl



void libLog(const LoggerEntry* log) { COUT(log->ToString().Buffer()); }


uint8_t* GetFirstThreeLayersRGBA(uint8_t *blendMapData, int dim, int elementSize)
{
	uint8_t *imageData = new uint8_t[dim * dim * 4]();
	int imageIndex, blendMapIndex;

	for (int i = 0; i < dim * dim; i++)
	{
		imageIndex = i * 4;
		blendMapIndex = i * elementSize;

		imageData[imageIndex]   = blendMapData[blendMapIndex];
		imageData[imageIndex+1] = blendMapData[blendMapIndex+1];
		imageData[imageIndex+2] = blendMapData[blendMapIndex+2];
		imageData[imageIndex+3] = 255;
	}

	return imageData;
}



int main()
{
	Logger::SetLogCallback(&libLog);

	const char* path1; 
	const char* path2;

#if defined( __APPLE__ )
	path1 = "/Users/will/Desktop/geo1.lvl";
	path2 = "/Users/will/Desktop/MLC.lvl";
#elif defined(_WIN32)
	path1 = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Star Wars Battlefront II\\GameData\\data\\_lvl_pc\\geo\\geo1.lvl";
	path2 = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Star Wars Battlefront II\\GameData\\data\\_lvl_pc\\kas\\kas2.lvl";
#else
	path1 = "/home/will/Desktop/geo1.lvl";
	path2 = "/home/will/Desktop/MLC.lvl";
#endif

	Level* testLVL1 = Level::FromFile(path1);
	Level* testLVL2 = Level::FromFile(path2);


	uint32_t dim, elementSize;

	uint8_t *blendMapData;

	const LibSWBF2::Wrappers::Terrain& terr1 = testLVL1 -> GetTerrains()[0];
	terr1.GetBlendMap(dim,elementSize,blendMapData);
	stbi_write_png("testsplat_blended.png", dim, dim, 4, reinterpret_cast<void *>(GetFirstThreeLayersRGBA(blendMapData,dim,elementSize)), dim*4);


	const LibSWBF2::Wrappers::Terrain& terr2 = testLVL2 -> GetTerrains()[0];
	terr2.GetBlendMap(dim,elementSize,blendMapData);
	stbi_write_png("testsplat_painted.png", dim, dim, 4, reinterpret_cast<void *>(GetFirstThreeLayersRGBA(blendMapData,dim,elementSize)), dim*4);

	return 0;
}
