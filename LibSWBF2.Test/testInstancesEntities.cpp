#include "testing.h"


int main(int ac, char **av)
{
	List<String> pathsInput;

	for (int i = 1; i < ac; i++)
	{
		pathsInput.Add(av[i]);
	}

	Container* container;
	auto testLVLs = LoadAndTrackLVLs(pathsInput, container);

	auto testLVL = testLVLs[0];


	const List<World>& worlds = testLVL -> GetWorlds();
	const List<EntityClass>& entities = testLVL -> GetEntityClasses();


	List<String> values;
	List<uint32_t> properties;

	const String geomProp("GeometryName");

	COUT("Listing all entities:");

	for (int i = 0; i < entities.Size(); i++)
	{
		COUT("\nType: " << entities[i].GetTypeName().Buffer() 
			<< "\nBase: " << entities[i].GetBaseName().Buffer()
		);


		continue;

		COUT("  Overridden properties: ");

		if (entities[i].GetOverriddenProperties(properties, values))
		{
			for (int j = 0; j < properties.Size(); j++)
			{
				COUT(fmt::format("    Hash: {}, Value: {}", properties[j], values[j].Buffer()).c_str());
			}
		}
		else 
		{
			COUT("    Failed to get overridden properties!");
		}
	}


	Container::Delete(container);

	return 0;
}
