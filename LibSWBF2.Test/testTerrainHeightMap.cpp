#ifdef _WIN32

#include "../LibSWBF2/LibSWBF2.h"
#include "../LibSWBF2/FileWriter.h"
#include "../LibSWBF2/Chunks/LVL/LVL.h"

#else

#include "LibSWBF2.h"
#include "FileWriter.h"
#include "Chunks/LVL/LVL.h"

#endif

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

#if defined( __APPLE__ )
	Level* testLVL = Level::FromFile("/Users/will/Desktop/geo1.lvl");
#elif defined(_WIN32)
	Level* testLVL = Level::FromFile("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Star Wars Battlefront II\\GameData\\data\\_lvl_pc\\geo\\geo1.lvl");
#else
	Level* testLVL = Level::FromFile("/home/will/Desktop/geo1.lvl");
#endif

	uint32_t dim, scale;
	float *heightMapData;

	const Terrain& terr = testLVL -> GetTerrains()[0];
	
	terr.GetHeightMap(dim,scale,heightMapData);
	stbi_write_png("geo1_test_windows.png", dim, dim, 4, reinterpret_cast<void *>(GetHeightMapWithHolesRGBA(heightMapData,dim)), dim*4);

	return 0;
}
