#include "testing.h"

// Adds then loads all lvl files passed.


int main(int ac, char** av)
{
	List<String> pathsInput;

	for (int i = 1; i < ac; i++)
	{
		pathsInput.Add(av[i]);
	}

	Container *container;
	auto lvlPtrs = LoadAndTrackLVLs(pathsInput, container);

	for (int i = 0; i < lvlPtrs.size(); i++)
	{
		const Level *lvl = lvlPtrs[i];
		COUT(lvl -> GetLevelName().Buffer() << " contains " << lvl -> GetModels().Size() << " models.");
	}

	Container::Delete(container);

	return 0;
}
