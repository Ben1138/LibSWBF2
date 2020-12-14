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


	COUT("\n==================  Listing all entities  ========================\n");

	for (int i = 0; i < entities.Size(); i++)
	{
		COUT("Found entity type: " << entities[i].GetTypeName().Buffer() 
			<< " which is subclass of " << entities[i].GetBaseName().Buffer()
		);
	}


	COUT("\n==================  Listing all instances  ========================\n");

	for (int i = 0; i < worlds.Size(); i++)
	{
		const List<Instance>& instances = worlds[i].GetInstances();
		
		for (int j = 0; j < instances.Size(); j++)
		{
			const String& name = instances[j].GetName();
			
			COUT("Found instance: " << name.Buffer() 
				<< " at position " << instances[j].GetPosition().ToString().Buffer()
			);			
		}
	}


	COUT("\n==================  Listing all instances with corresponding entity references  ========================\n");

	for (int i = 0; i < worlds.Size(); i++)
	{
		const List<Instance>& instances = worlds[i].GetInstances();
		
		for (int j = 0; j < instances.Size(); j++)
		{
			const String& name = instances[j].GetName();
			const String& instanceType = instances[j].GetType();

			auto *instanceClass = testLVL -> GetEntityClass(instanceType);
			String geometryName; 

			if (instanceClass != nullptr && instanceClass -> GetProperty(geomProp,geometryName))
			{
				COUT("Found instance: " << name.Buffer() 
					<< " of type " << instanceType.Buffer()
					<< " at position " << instances[j].GetPosition().ToString().Buffer()
					<< " with model name " << geometryName.Buffer()
				);
			}
		}
	}





	return 0;
}
