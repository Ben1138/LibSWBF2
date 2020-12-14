#include "testing.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stbi/stb_image_write.h"

/*
Visualizes the texture blending between
the first three layers of a terrain.
*/


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



int main(int ac, char** av)
{
	List<String> pathsInput;

	for (int i = 1; i < ac; i++)
	{
		pathsInput.Add(av[i]);
	}

	auto lvlPtrs = LoadAndTrackLVLs(pathsInput);

	uint32_t dim, elementSize;
	uint8_t *blendMapData;

	for (int i = 0; i < lvlPtrs.size(); i++)
	{
		const Level *lvl = lvlPtrs[i];
		std::string name = lvl -> GetLevelName().Buffer();
		name.replace(name.end() - 4, name.end(), ".png");

		const LibSWBF2::Wrappers::Terrain& terr = lvl -> GetTerrains()[0];
		terr.GetBlendMap(dim,elementSize,blendMapData);
		stbi_write_png(name.c_str(), dim, dim, 4, reinterpret_cast<void *>(GetFirstThreeLayersRGBA(blendMapData,dim,elementSize)), dim*4);
	}

	return 0;
}
