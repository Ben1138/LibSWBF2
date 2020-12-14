#include "testing.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stbi/stb_image_write.h"


/*
Visualizes terrain heightmaps w/png files, for quick sanity testing.
*/


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



int main(int ac, char** av)
{
	List<String> pathsInput;

	for (int i = 1; i < ac; i++)
	{
		pathsInput.Add(av[i]);
	}

	auto lvlPtrs = LoadAndTrackLVLs(pathsInput);

	uint32_t dim, scale;
	float *heightMapData;

	for (int i = 0; i < lvlPtrs.size(); i++)
	{
		const Level *lvl = lvlPtrs[i];
		std::string name = lvl -> GetLevelName().Buffer();
		name.replace(name.end() - 4, name.end(), ".png");

		const LibSWBF2::Wrappers::Terrain& terr = lvl -> GetTerrains()[0];
		terr.GetHeightMap(dim,scale,heightMapData);
		
		stbi_write_png(name.c_str(), dim, dim, 4, reinterpret_cast<void *>(GetHeightMapWithHolesRGBA(heightMapData,dim)), dim*4);
	}

	return 0;
}
