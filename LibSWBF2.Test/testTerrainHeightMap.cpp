#include "../LibSWBF2/LibSWBF2.h"
#include "../LibSWBF2/FileWriter.h"
#include "../LibSWBF2/Chunks/LVL/LVL.h"

#include <iostream>
#include <fstream>
#include <string>
<<<<<<< HEAD
=======
#include <unistd.h>
>>>>>>> a9e1bdb2f5dc62bc007c76ec1296c13b7ef5d9f9

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stbi/stb_image_write.h"

using LibSWBF2::Types::String;
using LibSWBF2::Types::List;
<<<<<<< HEAD

=======
using LibSWBF2::Container;

using namespace LibSWBF2::Chunks::LVL;
>>>>>>> a9e1bdb2f5dc62bc007c76ec1296c13b7ef5d9f9
using namespace LibSWBF2::Wrappers;

using LibSWBF2::Logging::Logger;
using LibSWBF2::Logging::LoggerEntry;


#define COUT(x) std::cout << x << std::endl



<<<<<<< HEAD
void libLog(const LoggerEntry* log){ COUT(log->ToString().Buffer()); }

=======
>>>>>>> a9e1bdb2f5dc62bc007c76ec1296c13b7ef5d9f9

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
<<<<<<< HEAD
	Logger::SetLogCallback(&libLog);

#if defined( __APPLE__ )
	Level* testLVL = Level::FromFile("/Users/will/Desktop/geo1.lvl");
#elif defined(_WIN32)
	Level* testLVL = Level::FromFile("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Star Wars Battlefront II\\GameData\\data\\_lvl_pc\\geo\\geo1.lvl");
#else
	Level* testLVL = Level::FromFile("/home/will/Desktop/geo1.lvl");
#endif

=======
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

>>>>>>> a9e1bdb2f5dc62bc007c76ec1296c13b7ef5d9f9
	uint32_t dim, scale;
	float *heightMapData;

	const LibSWBF2::Wrappers::Terrain& terr = testLVL -> GetTerrains()[0];
<<<<<<< HEAD
	
	terr.GetHeightMap(dim,scale,heightMapData);
	stbi_write_png("geo1_test.png", dim, dim, 4, reinterpret_cast<void *>(GetHeightMapWithHolesRGBA(heightMapData,dim)), dim*4);
=======
	terr.GetHeightMap(dim,scale,heightMapData); //segfault here
	
	stbi_write_png("height_test.png", dim, dim, 4, reinterpret_cast<void *>(GetHeightMapWithHolesRGBA(heightMapData,dim)), dim*4);
>>>>>>> a9e1bdb2f5dc62bc007c76ec1296c13b7ef5d9f9

	return 0;
}
