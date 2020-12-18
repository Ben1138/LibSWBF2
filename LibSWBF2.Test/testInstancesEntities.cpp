#include "testing.h"


int main(int ac, char **av)
{
	List<String> pathsInput;

	for (int i = 1; i < ac; i++)
	{
		pathsInput.Add(av[i]);
	}

	auto testLVL = LoadAndTrackLVLs(pathsInput)[0];


	const List<World>& worlds = testLVL -> GetWorlds();
	const List<EntityClass>& entities = testLVL -> GetEntityClasses();

	const String geomProp("GeometryName");


	COUT("Listing all entities:");

	for (int i = 0; i < entities.Size(); i++)
	{
		COUT("Found entity type: " << entities[i].GetTypeName().Buffer() 
			<< " which is subclass of " << entities[i].GetBaseName().Buffer()
		);
	}

	return 0;
}
