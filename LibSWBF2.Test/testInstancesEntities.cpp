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


	//for 




	/*
	List<String> values;
	List<uint32_t> properties;

	const String geomProp("GeometryName");

	COUT("Listing all entities:");

	for (int i = 0; i < entities.Size(); i++)
	{
		COUT("\nFound entity type: " << entities[i].GetTypeName().Buffer() 
			<< " which is subclass of " << entities[i].GetBaseName().Buffer()
		);

		COUT("  Overridden properties: ");

		if (entities[i].GetOverriddenProperties(properties, values))
		{
			for (int j = 0; j < properties.Size(); j++)
			{
				COUT(fmt::format("\tHash: {}, Value: {}", properties[j], values[j].Buffer()).c_str());
			}
		}
		else 
		{
			COUT("\tFailed to get overridden properties!");
		}
	}
	*/

	return 0;
}
