#include "testing.h"


int main(int ac, char** av)
{
	List<String> pathsInput;

	for (int i = 1; i < ac; i++)
	{
		pathsInput.Add(av[i]);
	}

	auto testLVLs = LoadAndTrackLVLs(pathsInput);


	for (int i = 0; i < testLVLs.size(); i++)
	{
		auto testLVL = testLVLs[i];

		COUT("Results for " << testLVL -> GetLevelName().Buffer());
		COUT("\t" << testLVL -> GetGlobalLighting() -> ToString().Buffer());

		const List<Light>& lights = testLVL -> GetLights();

		for (int j = 0; j < lights.Size(); j++)
		{
			Light lighti = lights[j];
			COUT("\t" << lighti.ToString().Buffer());
		}

	}

	return 0;
}
