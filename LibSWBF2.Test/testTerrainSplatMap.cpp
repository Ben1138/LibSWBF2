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

#ifdef __APPLE__
	Level *testLVL1 = Level::FromFile("/Users/will/Desktop/terrainblendinglvls/TST_Tex3_Blended.lvl");
	Level *testLVL2 = Level::FromFile("/Users/will/Desktop/terrainblendinglvls/TST_Tex3_Painted.lvl");
	//Level *testLVL2 = Level::FromFile("/Users/will/Desktop/MLC.lvl");
#else
	Level *testLVL1 = Level::FromFile("/home/will/Desktop/geo1.lvl");
	Level *testLVL2 = Level::FromFile("/home/will/Desktop/hole.lvl");
	//Level *testLVL = Level::FromFile("/home/will/Desktop/geo1.lvl");
#endif


	uint32_t dim, elementSize;
	uint8_t *blendMapData;

	const Terrain& terr1 = testLVL1 -> GetTerrains()[0];
	terr1.GetBlendMap(dim,elementSize,blendMapData);
	stbi_write_png("testsplat_blended.png", dim, dim, 4, reinterpret_cast<void *>(GetFirstThreeLayersRGBA(blendMapData,dim,elementSize)), dim*4);


	const Terrain& terr2 = testLVL2 -> GetTerrains()[0];
	terr2.GetBlendMap(dim,elementSize,blendMapData);
	stbi_write_png("testsplat_painted.png", dim, dim, 4, reinterpret_cast<void *>(GetFirstThreeLayersRGBA(blendMapData,dim,elementSize)), dim*4);

	return 0;
}
