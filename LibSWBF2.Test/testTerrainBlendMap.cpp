#include "../LibSWBF2/LibSWBF2.h"
#include "../LibSWBF2/FileWriter.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stbi/stb_image_write.h"

using LibSWBF2::Types::String;
using LibSWBF2::Types::List;
using LibSWBF2::Wrappers::Terrain;
using LibSWBF2::Container;


using namespace LibSWBF2::Wrappers;

using LibSWBF2::Logging::Logger;
using LibSWBF2::Logging::LoggerEntry;


#define COUT(x) std::cout << x << std::endl




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
	const char* path1;
	const char* path2;

#ifdef __APPLE__
	path1 = "/Users/will/Desktop/terrainblendinglvls/TST_Tex3_Blended.lvl";
	path2 = "/Users/will/Desktop/terrainblendinglvls/TST_Tex3_Painted.lvl";
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
	}

	Level *testLVL1 = container -> GetLevel(handle1);
	Level *testLVL2 = container -> GetLevel(handle2);

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
