#include "../LibSWBF2/LibSWBF2.h"
#include "../LibSWBF2/FileWriter.h"
#include "../LibSWBF2/Chunks/LVL/LVL.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stbi/stb_image_write.h"

using LibSWBF2::Types::String;
using LibSWBF2::Types::List;
using LibSWBF2::Container;

using namespace LibSWBF2::Chunks::LVL;
using namespace LibSWBF2::Wrappers;

using LibSWBF2::Logging::Logger;
using LibSWBF2::Logging::LoggerEntry;


#define COUT(x) std::cout << x << std::endl



void libLog(const LoggerEntry* log){ COUT(log->ToString().Buffer()); }


uint8_t* GetHeightMapWithHolesRGBA(float *heightMapData, int dim)
{
	uint8_t *imageData = new uint8_t[dim * dim * 4]();
	int imageIndex;

	for (int i = 0; i < dim * dim; i++)
	{
		imageIndex = i * 4;
		float curHeight = heightMapData[i];

		uint8_t h = (uint8_t) (curHeight * 255.0f);
		imageData[imageIndex]   = h;
		imageData[imageIndex+1] = h;
		imageData[imageIndex+2] = h;

		if (curHeight < -.01)
		{
			imageData[imageIndex] = 255;
			imageData[imageIndex + 1] = 0;
			imageData[imageIndex + 2] = 0;
		}
	
		imageData[imageIndex+3] = 255;
	}

	return imageData;
}



int main()
{
	Logger::SetLogCallback(&libLog);

	const char *path;

#ifdef __APPLE__
	path = "/Users/will/Desktop/geo1.lvl";
#else
	path = "/home/will/Desktop/geo1.lvl";
#endif

	Container *container = Container::Create();
	auto handle = container -> AddLevel(path);
	container -> StartLoading();

	while (!container -> IsDone())
	{
		usleep(100000);
	}

	Level *testLVL = container -> GetLevel(handle);

	uint32_t dim, scale;
	float *heightMapData;

	const LibSWBF2::Wrappers::Terrain& terr = testLVL -> GetTerrains()[0];
	terr.GetHeightMap(dim,scale,heightMapData); //segfault here
	
	stbi_write_png("height_test.png", dim, dim, 4, reinterpret_cast<void *>(GetHeightMapWithHolesRGBA(heightMapData,dim)), dim*4);

	return 0;
}
